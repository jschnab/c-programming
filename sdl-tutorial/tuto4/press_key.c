#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum key_surfaces {
    KEY_SURFACE_DEFAULT,
    KEY_SURFACE_UP,
    KEY_SURFACE_DOWN,
    KEY_SURFACE_LEFT,
    KEY_SURFACE_RIGHT,
    KEY_SURFACE_TOTAL
};

bool initialize();
bool load_media();
void close_all();
SDL_Surface *load_surface(char *);

SDL_Window *window = NULL;
SDL_Surface *window_surface = NULL;
SDL_Surface *key_surfaces[KEY_SURFACE_TOTAL];
SDL_Surface *current_surface = NULL;


bool initialize() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        success = false;
    }
    else {
        window = SDL_CreateWindow(
            "SDL Tuto 4",
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
    key_surfaces[KEY_SURFACE_DEFAULT] = load_surface("press.bmp");
    if (key_surfaces[KEY_SURFACE_DEFAULT] == NULL) {
        fprintf(stderr, "SDL could not load image %s: %s\n", "press.bmp", SDL_GetError());
        success = false;
    }
    key_surfaces[KEY_SURFACE_UP] = load_surface("up.bmp");
    if (key_surfaces[KEY_SURFACE_UP] == NULL) {
        fprintf(stderr, "SDL could not load image %s: %s\n", "up.bmp", SDL_GetError());
        success = false;
    }
    key_surfaces[KEY_SURFACE_DOWN] = load_surface("down.bmp");
    if (key_surfaces[KEY_SURFACE_DOWN] == NULL) {
        fprintf(stderr, "SDL could not load image %s: %s\n", "down.bmp", SDL_GetError());
        success = false;
    }
    key_surfaces[KEY_SURFACE_LEFT] = load_surface("left.bmp");
    if (key_surfaces[KEY_SURFACE_LEFT] == NULL) {
        fprintf(stderr, "SDL could not load image %s: %s\n", "left.bmp", SDL_GetError());
        success = false;
    }
    key_surfaces[KEY_SURFACE_RIGHT] = load_surface("right.bmp");
    if (key_surfaces[KEY_SURFACE_RIGHT] == NULL) {
        fprintf(stderr, "SDL could not load image %s: %s\n", "right.bmp", SDL_GetError());
        success = false;
    }
    return success;
}


void close_all() {
    for (int i = 0; i < KEY_SURFACE_TOTAL; i++) {
        SDL_FreeSurface(key_surfaces[i]);
        key_surfaces[i] = NULL;
    }
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}


SDL_Surface *load_surface(char *path) {
    SDL_Surface *surface = SDL_LoadBMP(path);
    if (surface == NULL) {
        fprintf(stderr, "SDL could not load image %s: %s\n", path, SDL_GetError());
    }
    return surface;
}


int main(int argc, char *argv[]) {
    if (initialize()) {
        if (load_media()) {
            bool quit = false;
            SDL_Event e;
            current_surface = key_surfaces[KEY_SURFACE_DEFAULT];
            SDL_BlitSurface(current_surface, NULL, window_surface, NULL);
            SDL_UpdateWindowSurface(window);
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    else if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                                current_surface = key_surfaces[KEY_SURFACE_UP];
                                break;
                            case SDLK_DOWN:
                                current_surface = key_surfaces[KEY_SURFACE_DOWN];
                                break;
                            case SDLK_LEFT:
                                current_surface = key_surfaces[KEY_SURFACE_LEFT];
                                break;
                            case SDLK_RIGHT:
                                current_surface = key_surfaces[KEY_SURFACE_RIGHT];
                                break;
                            default:
                                current_surface = key_surfaces[KEY_SURFACE_DEFAULT];
                        }
                        SDL_BlitSurface(current_surface, NULL, window_surface, NULL);
                        SDL_UpdateWindowSurface(window);
                    }
                }
            }
        }
    }
    close_all();
    return 0;
}
