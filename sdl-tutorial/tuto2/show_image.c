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
SDL_Surface *hello = NULL;


bool initialize() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO != 0)) {
        fprintf(stderr, "SDL could not initialize: %s\n", SDL_GetError());
        success = false;
    }
    else {
        gwindow = SDL_CreateWindow(
            "SDL tutorial 2",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0  /* window will be shown by default */
        );
        if (gwindow == NULL) {
            fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
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
    hello = SDL_LoadBMP("hello.bmp");
    if (hello == NULL) {
        fprintf(stderr, "Unable to load image %s: %s\n", "hello.bmp", SDL_GetError());
        success = false;
    }
    return success;
}


void close_all() {
    SDL_FreeSurface(hello);
    hello = NULL;
    SDL_DestroyWindow(gwindow);
    gwindow = NULL;
    SDL_Quit();
}


int main(int argc, char *argv[]) {
    if (initialize()) {
        if (load_media()) {
            SDL_BlitSurface(
                hello,    /* source suface */
                NULL,     /* source rectangle structure, NULL to copy entire surface */
                gsurface, /* destination surface */
                NULL      /* destination surface, NULL to copy entire surface */
            );
            SDL_UpdateWindowSurface(gwindow);
            SDL_Delay(2000);
        }
    }
    close_all();
    return 0;
}
