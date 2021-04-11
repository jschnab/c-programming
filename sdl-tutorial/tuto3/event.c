#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool initialize();
bool load_media();
void close_all();

SDL_Window *gwindow = NULL;
SDL_Surface *gsurface = NULL;
SDL_Surface *xout = NULL;


bool initialize() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL could not initialize: %s\n", SDL_GetError());
        success = false;
    }
    else {
        gwindow = SDL_CreateWindow(
            "SDL Tuto 3",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0
        );
        if (gwindow == NULL) {
            printf("Window could not be created: %s\n", SDL_GetError());
            success = false;
        }
        else {
            gsurface = SDL_GetWindowSurface(gwindow);
        }
    }
    return success;
}


bool load_media() {
    bool success = true;
    xout = SDL_LoadBMP("xout.bmp");
    if (xout == NULL) {
        fprintf(stderr, "Could not load image %s: %s\n", "xout.bmp", SDL_GetError());
        success = false;
    }
    return success;
}


void close_all() {
    SDL_FreeSurface(xout);
    xout = NULL;
    SDL_DestroyWindow(gwindow);
    gwindow = NULL;
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
                    SDL_BlitSurface(
                        xout,
                        NULL,
                        gsurface,
                        NULL
                    );
                    SDL_UpdateWindowSurface(gwindow);
                }
            }
        }
    }
    close_all();
    return 0;
}
