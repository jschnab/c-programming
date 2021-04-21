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

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;


bool initialize() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not initialize: %s\n", SDL_GetError());
        success = false;
    }
    else {
        /* set texture filtering to linear */
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            fprintf(stderr, "Linear texture filtering not enabled");
        }

        window = SDL_CreateWindow(
            "SDL Tuto 7",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0
        );
        if (window == NULL) {
            fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
            success = false;
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                fprintf(stderr, "Renderer could not be created: %s\n", SDL_GetError());
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int img_flags = IMG_INIT_PNG;
                if (!(IMG_Init(img_flags) & img_flags)) {
                    fprintf(stderr, "SDL_Image could not initialize: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}


bool load_media() {
    bool success = true;
    texture = load_texture("texture.png");
    if (texture == NULL) {
        fprintf(stderr, "Failed to load texture image");
        success = false;
    }
    return success;
}


void close_all() {
    SDL_DestroyTexture(texture);
    texture = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
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
        final_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if (final_texture == NULL) {
            fprintf(stderr, "Could not create texture from '%s': %s\n", path, IMG_GetError());
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
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);
            }
        }
    }
    close_all();
    return 0;
}
