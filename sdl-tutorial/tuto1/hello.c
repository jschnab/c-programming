#include <SDL2/SDL.h>
#include <stdio.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char *argv[]) {  /* these arg types are required by SDL */
    SDL_Window *window = NULL;
    SDL_Surface *screen_surface = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
    }
    else {
        window = SDL_CreateWindow(
            "SDL Tuto",               /* title of the window */
            SDL_WINDOWPOS_UNDEFINED,  /* x position */
            SDL_WINDOWPOS_UNDEFINED,  /* y position */
            SCREEN_WIDTH,             /* window width */
            SCREEN_HEIGHT,            /* window height */
            SDL_WINDOW_SHOWN          /* flags, this one is actually ignored, so we can pass 0 */
        );
        if (window == NULL) {
            fprintf(stderr, "Window could not be created. SDL_Error: %s\n", SDL_GetError());
        }
        else {
            screen_surface = SDL_GetWindowSurface(window);
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
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
