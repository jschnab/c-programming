#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool initialize();
bool load_media();
void close_all();
SDL_Texture *load_texture(char *);

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gTexture = NULL;


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
            "SDL Tuto 9",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0
        );
        if (gWindow == NULL) {
            fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int img_flags = IMG_INIT_PNG;
                if ( !(IMG_Init(img_flags) & img_flags)) {
                    fprintf(stderr, "SDL_image could not initialize: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}


bool load_media() {
    bool success = true;
    gTexture = load_texture("viewport.png");
    if (gTexture == NULL) {
        fprintf(stderr, "Could not load texture image: %s\n", IMG_GetError());
        success = false;
    }
    return success;
}


void close_all() {
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    IMG_Quit();
    SDL_Quit();
}


SDL_Texture *load_texture(char *path) {
    SDL_Texture *final_texture = NULL;
    SDL_Surface *loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        fprintf(stderr, "Could not load image '%s': %s\n", path, IMG_GetError());
    }
    else {
        final_texture = SDL_CreateTextureFromSurface(gRenderer, loaded_surface);
        if (final_texture == NULL) {
            fprintf(stderr, "Could not create texture from surface: %s\n", SDL_GetError());
        }
        SDL_FreeSurface(loaded_surface);
    }
    return final_texture;
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

                /* top left viewport */
                SDL_Rect top_left;
                top_left.x = 0;
                top_left.y = 0;
                top_left.w = SCREEN_WIDTH / 2;
                top_left.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(gRenderer, &top_left);

                /* render texture to screen */
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                /* top right */
                SDL_Rect top_right;
                top_right.x = SCREEN_WIDTH / 2;
                top_right.y = 0;
                top_right.w = SCREEN_WIDTH / 2;
                top_right.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(gRenderer, &top_right);

                /* render texture to screen */
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                /* bottom */
                SDL_Rect bottom;
                bottom.x = 0;
                bottom.y = SCREEN_HEIGHT / 2;
                bottom.w = SCREEN_WIDTH;
                bottom.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(gRenderer, &bottom);

                /* render texture to screen */
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                /* update screen */
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    close_all();
    return 0;
}
