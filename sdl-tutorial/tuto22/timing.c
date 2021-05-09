#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdint.h>
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
LTexture gTimeTexture;
LTexture gPromptTexture;


void close_all() {
    ltexture_destroy(&gTimeTexture);
    ltexture_destroy(&gPromptTexture);
    TTF_CloseFont(gFont);
    gFont = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


bool initialize() {
    check(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL failed to initialize: %s", SDL_GetError());
    check(
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"),
        "Linear texture filtering not enabeld"
    );
    gWindow = SDL_CreateWindow(
        "SDL Tuto 22",
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
        "SDL_ttf could not initialize: %s",
        TTF_GetError()
    );
    return true;

    error:
        return false;
}


bool load_media() {
    gFont = TTF_OpenFont("lazy.ttf", 28);
    check(gFont != NULL, "Failed to load 'lazy.ttf': %s", TTF_GetError());
    SDL_Color text_color = {0, 0, 0, 255};
    check(
        ltexture_from_text(
            &gPromptTexture,
            "Press <Enter> to reset start time",
            text_color
        ),
        "Failed to render prompt texture"
    );
    return true;

    error:
        return false;
}


void ltexture_destroy(LTexture *t) {
    if (t->texture != NULL) {
        SDL_DestroyTexture(t->texture);
        t->texture = NULL;
        t->width = 0;
        t->height = 0;
    }
}


bool ltexture_from_text(LTexture *t, char *text, SDL_Color color) {
    ltexture_destroy(t);
    SDL_Surface *text_surface = TTF_RenderText_Solid(gFont, text, color);
    check_mem(text_surface);
    t->texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);
    check_mem(t->texture);
    t->width = text_surface->w;
    t->height = text_surface->h;
    SDL_FreeSurface(text_surface);
    return true;

    error:
        return false;
}


void ltexture_render(LTexture *t, int x, int y, SDL_Rect *clip) {
    SDL_Rect render_quad = {x, y, t->width, t->height};
    if (clip != NULL) {
        render_quad.x = clip->x;
        render_quad.y = clip->y;
    }
    SDL_RenderCopy(gRenderer, t->texture, clip, &render_quad);
}


int main(int argc, char *argv[]) {
    check(initialize(), "Failed to initialize");
    check(load_media(), "Failed to load media");
    bool quit = false;
    SDL_Event e;
    SDL_Color text_color = {0, 0, 0, 255};
    uint32_t start = 0;
    char text[100];
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                start = SDL_GetTicks();
            }
        }
        sprintf(text, "Milliseconds since start time %u", SDL_GetTicks() - start);
        check(
            ltexture_from_text(&gTimeTexture, text, text_color),
            "Failed to render time texture"
        );
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        ltexture_render(
            &gPromptTexture,
            (SCREEN_WIDTH - gPromptTexture.width) / 2,
            0,
            NULL
        );
        ltexture_render(
            &gTimeTexture,
            (SCREEN_WIDTH - gPromptTexture.width) / 2,
            (SCREEN_HEIGHT - gPromptTexture.height) / 2,
            NULL
        );
        SDL_RenderPresent(gRenderer);
    }
    close_all();
    return 0;

    error:
        close_all();
        return -1;
}
