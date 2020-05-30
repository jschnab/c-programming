#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

char init();

char loadMedia();

void quit();

SDL_Window *gWindow = NULL;

SDL_Surface *gScreenSurface = NULL;

SDL_Surface *gImage = NULL;

int main (int argc, char *argv[]) {

    if (!init())
        printf("Failed to initialize.\n");
    else
    {
        if (!loadMedia())
            printf("Failed to load media.\n");
        else
        {
            // main loop quit signal
            char quit_sig = 0;

            // event handler
            SDL_Event e;

            // while app is running
            while (!quit_sig)
            {
                // handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    // user requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit_sig = 1;
                    }
                }

                // apply the image
                SDL_BlitSurface(
                        gImage,
                        NULL,
                        gScreenSurface,
                        NULL
                        );
                // update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
    quit();
    return 0;
}


char init() {
    char success = 1;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize.\nSDL Error: %s\n", SDL_GetError());
        success = 0;
    } else {
        gWindow = SDL_CreateWindow(
                "SDL tutorial 3",
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
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

char loadMedia() {
    char success = 1;
    gImage = SDL_LoadBMP("img.bmp");
    if (gImage == NULL) {
        printf("Unable to load image.\nSDL Error: %s\n", SDL_GetError());
        success = 0;
    }
    return success;
}

void quit() {
    SDL_FreeSurface(gImage);
    gImage = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}
