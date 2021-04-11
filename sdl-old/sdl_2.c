#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

// starts up SDL and creates window
char init();

char loadMedia();

// frees media and shut down SDL
void quit();

// the window we render into
SDL_Window *gWindow = NULL;

// the surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// the image we load and show on the screen
SDL_Surface *gImage = NULL;

int main (int argc, char *argv[]) {
    // startup SDL and create window
    if (!init()) {
        printf("Failed to initilize.\n");
    } else {
        // load media
        if (!loadMedia()) {
            printf("Failed to load media.\n");
        } else {
            // apply the image
            SDL_BlitSurface(
                    gImage,
                    NULL,
                    gScreenSurface,
                    NULL
            );
            // update the surface
            SDL_UpdateWindowSurface(gWindow);

            // wait two seconds
            SDL_Delay(2000);
        }
    }
    // free resources and close SDL
    quit();

    return 0;
}

char init() {

    // initialization flag
    char success = 1;

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize.\nSDL_Error: %s\n", SDL_GetError());
        success = 0;
    } else {
        // create window
        gWindow = SDL_CreateWindow(
                "SDL tutorial",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN
        );
        if (gWindow == NULL) {
            printf("Window could not be created.\nSDL Error: %s\n", SDL_GetError());
            success = 0;
        } else {
            // get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

char loadMedia() {

    char success = 1;

    // load image
    gImage = SDL_LoadBMP("img.bmp");
    if (gImage == NULL) {
        printf("Unable to load image.\nSDL Error: %s\n", SDL_GetError());
        success = 0;
    }
    return success;
}

void quit() {
    // de-allocate surface
    SDL_FreeSurface(gImage);
    gImage = NULL;

    // destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // quit SDL subsystems
    SDL_Quit();
}
