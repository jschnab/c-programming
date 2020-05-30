#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main (int argc, char *args[]) {

    // the window we are rendering to
    SDL_Window *window = NULL;

    // the surface contained by the window
    SDL_Surface *screenSurface = NULL;

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initialized.\nSDL Error: %s\n", SDL_GetError());
    }

    else {
        window = SDL_CreateWindow(
                "SDL Tutorial",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN
        );

        if (window == NULL) {
            printf("Window could not be created.\nSDL Error: %s\n", SDL_GetError());
        }

        else {
            // get window surface
            screenSurface = SDL_GetWindowSurface(window);

            // fill the surface with white
            SDL_FillRect(
                    screenSurface,
                    NULL,
                    SDL_MapRGB(
                        screenSurface->format,
                        0xFF,
                        0xFF,
                        0xFF
                    )
            );

            // update the surface
            SDL_UpdateWindowSurface(window);

            // wait two seconds
            SDL_Delay(2000);

            // destroy window and quit SDL subsystems
            SDL_DestroyWindow(window);
            SDL_Quit();

            return 0;
        }
    }
}
