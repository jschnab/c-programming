#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool initialize();
bool load_media();
void close_all();
SDL_Surface *load_surface(char *path);

SDL_Window *window = NULL;
SDL_Surface *window_surface = NULL;
SDL_Surface *stretched_surface = NULL;


bool initialize() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL could not initialize: %s\n", SDL_GetError());
        success = false;
    }
    else {
        window = SDL_CreateWindow(
            "SDL Tuto 5",
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
            window_surface = SDL_GetWindowSurface(window);
        }
    }
    return success;
}


bool load_media() {
    bool success = true;
    stretched_surface = load_surface("stretch.bmp");
    if (stretched_surface == NULL) {
        fprintf(stderr, "SDL could not load %s: %s\n", "stretch.bmp", SDL_GetError());
        success = false;
    }
    return success;
}


void close_all() {
    SDL_FreeSurface(stretched_surface);
    stretched_surface = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}


SDL_Surface *load_surface(char *path) {
    SDL_Surface *optimized_surface = NULL;
    SDL_Surface *loaded_surface = SDL_LoadBMP(path);
    if (loaded_surface == NULL) {
        fprintf(stderr, "SDL could not load raw image %s: %s\n", path, SDL_GetError());
    }
    else {
        optimized_surface = SDL_ConvertSurface(loaded_surface, window_surface->format, 0);
        if (optimized_surface == NULL) {
            fprintf(stderr, "SDL could not optimize image %s: %s\n", path, SDL_GetError());
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
                    SDL_Rect stretch_rect;
                    stretch_rect.x = 0;
                    stretch_rect.y = 0;
                    stretch_rect.w = SCREEN_WIDTH;
                    stretch_rect.h = SCREEN_HEIGHT;
                    SDL_BlitScaled(stretched_surface, NULL, window_surface, &stretch_rect);
                    SDL_UpdateWindowSurface(window);
                }
            }
        }
    }
    close_all();
    return 0;
}
