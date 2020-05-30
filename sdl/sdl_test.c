#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

void pause();

int main (int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);

    pause();

    SDL_Quit();

    return EXIT_SUCCESS;
}

void pause () {
    int keepOn = 1;
    SDL_Event event;

    while (keepOn) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                keepOn = 0;
        }
    }
}
