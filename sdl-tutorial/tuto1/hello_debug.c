#include <SDL2/SDL.h>
#include <stdio.h>
#include "../debug.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char *argv[]) {  /* these arg types are required by SDL */
    SDL_Window *window = NULL;
    SDL_Surface *screen_surface = NULL;

    check(SDL_Init(SDL_INIT_VIDEO) ==  0, "SDL could not initialize: %s\n", SDL_GetError());

    window = SDL_CreateWindow(
        "SDL Tuto",               /* title of the window */
        SDL_WINDOWPOS_UNDEFINED,  /* x position */
        SDL_WINDOWPOS_UNDEFINED,  /* y position */
        SCREEN_WIDTH,             /* window width */
        SCREEN_HEIGHT,            /* window height */
        SDL_WINDOW_SHOWN          /* flags, this one is actually ignored, so we can pass 0 */
    );
    check(window != NULL, "Could not create main window: %s\n", SDL_GetError());

    screen_surface = SDL_GetWindowSurface(window);
    check_mem(screen_surface);

    SDL_FillRect(
        screen_surface,
        NULL,  /* SDL_Rect structure representing the rectangle to fill, NULL fills entire surface */
        SDL_MapRGB(
            screen_surface->format,  /* SDL_PixelFormat structure */
            0xFF,                    /* red  */
            0xFF,                    /* green */
            0xFF                     /* blue */
        )
    );

    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

    error:
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
}
