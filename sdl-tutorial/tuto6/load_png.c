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

SDL_Surface *load_surface(char *);
SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
SDL_Surface *png_surface = NULL;


bool initialize() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL could not initialize: %s\n", SDL_GetError());
        success = false;
    }
    else {
        window = SDL_CreateWindow(
            "SDL Tuto 6",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0
        );
        if (window == NULL) {
            fprintf(stderr, "SDL could not create window: %s\n", SDL_GetError());
            success = false;
        }
        else {
            int image_flags = IMG_INIT_PNG;
            if (IMG_Init(image_flags) & image_flags) {
                surface = SDL_GetWindowSurface(window);
            }
            else {
                fprintf(stderr, "SDL could not initialize: %s\n", IMG_GetError());
                success = false;
            }
        }
    }
    return success;
}


bool load_media() {
    bool success = true;
    png_surface = load_surface("test.png");
    if (png_surface == NULL) {
        fprintf(stderr, "SDL failed to load PNG image\n");
        success = false;
    }
    return success;
}


void close_all() {
    SDL_FreeSurface(png_surface);
    png_surface = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    IMG_Quit();
    SDL_Quit();
}


SDL_Surface *load_surface(char *path) {
    SDL_Surface *optimized_surface = NULL;
    SDL_Surface *loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        fprintf(stderr, "Could not load image %s: %s\n", path, IMG_GetError());
    }
    else {
        optimized_surface = SDL_ConvertSurface(loaded_surface, surface->format, 0);
        if (optimized_surface == NULL) {
            fprintf(stderr, "Could not optimize image %s: %s\n", path, SDL_GetError());
        }
        SDL_FreeSurface(loaded_surface);
    }
    return optimized_surface;
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
                SDL_BlitSurface(png_surface, NULL, surface, NULL);
                SDL_UpdateWindowSurface(window);
            }
        }
    }
    close_all();
    return 0;
}
