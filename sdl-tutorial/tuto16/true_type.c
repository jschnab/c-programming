#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


typedef struct ltexture {
    SDL_Texture *texture;
    int width;
    int height;
} LTexture;


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;
LTexture text_texture = {NULL, 0, 0};


void close_all();
bool initialize();
bool load_media();
void ltexture_destroy(LTexture *);
bool ltexture_from_rendered_text(LTexture *, char *, SDL_Color);
void ltexture_render(LTexture *, int, int, SDL_Rect *);


void ltexture_render(LTexture * t, int x, int y, SDL_Rect *clip) {
    SDL_Rect render_quad = {x, y, t->width, t->height};
    if (clip != NULL) {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, t->texture, clip, &render_quad);
}


bool ltexture_from_rendered_text(LTexture *texture, char *text, SDL_Color text_color) {
    ltexture_destroy(texture);
    SDL_Surface *text_surface = TTF_RenderText_Solid(gFont, text, text_color);
    if (text_surface == NULL) {
        fprintf(stderr, "Could not render text surface: %s\n", TTF_GetError());
    }
    else {
        texture->texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);
        if (texture->texture == NULL) {
            fprintf(stderr, "Could not create texture from rendered text: %s\n", SDL_GetError());
        }
        else {
            texture->width = text_surface->w;
            texture->height = text_surface->h;
        }
        SDL_FreeSurface(text_surface);
    }
    return texture->texture != NULL;
}


void ltexture_destroy(LTexture *t) {
    if (t->texture != NULL) {
        SDL_DestroyTexture(t->texture);
        t->texture = NULL;
        t->width = 0;
        t->height = 0;
    }
}


bool initialize() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL could not initialize: %s\n", SDL_GetError());
        success = false;
    }
    else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            fprintf(stdout, "Linear texture filtering not enabled\n");
        }
        gWindow = SDL_CreateWindow(
            "SDL Tuto 16",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0
        );
        if (gWindow == NULL) {
            fprintf(stderr, "Could not create main window: %s\n", SDL_GetError());
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(
                gWindow,
                -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
            );
            if (gRenderer == NULL) {
                fprintf(stderr, "Could not create main renderer: %s\n", SDL_GetError());
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int img_flags = IMG_INIT_PNG;
                if (!(IMG_Init(img_flags) & img_flags)) {
                    fprintf(stderr, "SDL_image could not initialize: %s\n", IMG_GetError());
                    success = false;
                }
            }
            if (TTF_Init() == -1) {
                fprintf(stderr, "SDL_ttf could not initialize: %s\n", TTF_GetError());
                success = false;
            }
        }
    }
    return success;
}


bool load_media () {
    bool success = true;
    gFont = TTF_OpenFont("lazy.ttf", 28);
    if (gFont == NULL) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        success = false;
    }
    else {
        SDL_Color text_color = {0, 0, 0, 0};
        if (!ltexture_from_rendered_text(
                &text_texture,
                "The quick brown fox jumps over the lazy dog",
                text_color
        )) {
            fprintf(stderr, "Could not render text texture\n");
            success = false;
        }
    }
    return success;
}


void close_all() {
    ltexture_destroy(&text_texture);
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


int main(int argc, char *argv[]) {
    if (initialize()) {
        if (load_media()) {
            bool quit = false;
            SDL_Event e;
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                ltexture_render(
                    &text_texture,
                    (SCREEN_WIDTH - text_texture.width) / 2,
                    (SCREEN_HEIGHT - text_texture.height) / 2,
                    NULL
                );
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    close_all();
    return 0;
}
