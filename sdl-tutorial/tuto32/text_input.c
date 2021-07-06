#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../debug.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


typedef struct ltexture {
    SDL_Texture *texture;
    int width;
    int height;
} LTexture;


void close_all();
bool initialize();
bool load_media();
void ltexture_destroy(LTexture *);
bool ltexture_from_text(LTexture *, char *, SDL_Color);
void ltexture_render(LTexture *, int, int, SDL_Rect *);


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;

LTexture gPromptTexture = {NULL, 0, 0};
LTexture gInputTexture = {NULL, 0, 0};


void close_all() {
    ltexture_destroy(&gPromptTexture);
    ltexture_destroy(&gInputTexture);
    TTF_CloseFont(gFont);
    gFont = NULL;
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


bool initialize() {
    check(
        SDL_Init(SDL_INIT_VIDEO) == 0,
        "SDL failed to initialize: %s",
        SDL_GetError()
    );
    check(
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"),
        "Linear texture filtering is not enabled"
    );
    gWindow = SDL_CreateWindow(
        "SDL Tuto 32",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );
    check_mem(gWindow);
    gRenderer = SDL_CreateRenderer(
        gWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    check_mem(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int img_flags = IMG_INIT_PNG;
    check(
        IMG_Init(img_flags) & img_flags,
        "SDL_image failed to initialize: %s",
        IMG_GetError()
    );
    check(
        TTF_Init() == 0,
        "SDL_ttf failed to initialize: %s",
        TTF_GetError()
    );
    return true;

    error:
        return false;
}


bool load_media() {
    gFont = TTF_OpenFont("lazy.ttf", 28);
    check_mem(gFont);
    SDL_Color text_color = {0, 0, 0, 0xFF};
    check(
        ltexture_from_text(&gPromptTexture, "Enter text:", text_color),
        "Failed to render prompt text"
    );
    return true;

    error:
        return false;
}


void ltexture_destroy(LTexture *t) {
    if (t->texture != NULL) {
        SDL_DestroyTexture(t->texture);
        t->texture = NULL;
    }
    t->width = 0;
    t->height = 0;
}


bool ltexture_from_text(LTexture *t, char *text, SDL_Color color) {
    ltexture_destroy(t);
    SDL_Surface *text_surface = TTF_RenderText_Solid(gFont, text, color);
    check_mem(text_surface);
    t->texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);
    check_mem(t->texture);
    t->width = text_surface->w;
    t->height = text_surface->h;
    return true;

    error:
        SDL_FreeSurface(text_surface);
        return false;
}


void ltexture_render(LTexture *t, int x, int y, SDL_Rect *clip) {
    SDL_Rect render_quad = {x, y, t->width, t->height};
    if (clip != NULL) {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, t->texture, clip, &render_quad);
}


int main(int argc, char *argv[]) {
    check(initialize(), "Failed to initialize");
    check(load_media(), "Failed to load media");

    bool quit = false;
    SDL_Event e;
    SDL_Color text_color = {0, 0, 0, 0xFF};
    char input_text[40] = "Some text";
    ltexture_from_text(&gInputTexture, input_text, text_color);
    SDL_StartTextInput();

    while (!quit) {
        bool render_text = false;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                /* handle backspace */
                if (e.key.keysym.sym == SDLK_BACKSPACE && strlen(input_text) > 0) {
                    input_text[strlen(input_text)-1] = '\0';
                    render_text = true;
                }
                /* handle copy */
                else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                    SDL_SetClipboardText(input_text);
                }
                /* handle paste */
                else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                    strcpy(input_text, SDL_GetClipboardText());
                    render_text = true;
                }
            }

            /* special text input event */
            else if (e.type == SDL_TEXTINPUT) {
                /* ignore copy or pasting */
                if (!(SDL_GetModState() & KMOD_CTRL && (
                        e.text.text[0] == 'c' ||
                        e.text.text[0] == 'C' ||
                        e.text.text[0] == 'v' ||
                        e.text.text[0] == 'V'
                ))) {
                    /* append text */
                    strcat(input_text, e.text.text);
                    render_text = true;
                }
            }
        }

        /* render text if needed */
        if (render_text) {
            if (strlen(input_text) > 0) {
                ltexture_from_text(&gInputTexture, input_text, text_color);
            }
            else {
                ltexture_from_text(&gInputTexture, " ", text_color);
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        ltexture_render(
            &gPromptTexture,
            (SCREEN_WIDTH - gPromptTexture.width) / 2,
            0,
            NULL
        );
        ltexture_render(
            &gInputTexture,
            (SCREEN_WIDTH - gInputTexture.width) / 2,
            gPromptTexture.height,
            NULL
        );
        SDL_RenderPresent(gRenderer);
    }

    SDL_StopTextInput();
    close_all();
    return 0;

    error:
        close_all();
        return -1;
}
