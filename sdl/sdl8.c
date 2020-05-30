/* lazyfoo tutorial 8 : rendering rectangles */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

char init();

char loadMedia();

void quit();

SDL_Texture *loadTexture(char *path);

SDL_Window *gWindow = NULL;

SDL_Renderer *gRenderer = NULL;

int main(int argc, char *argv[]) {

    if (!init()) {
        printf("Failed to initialize.\n");
    }
    else
    {
        if (!loadMedia) {
            printf("Failed to load media.\n");
        }
        else
        {
            char quit_sig = 0;

            SDL_Event e;

            while (!quit_sig) {

                while (SDL_PollEvent(&e) != 0) {

                    if (e.type == SDL_QUIT)
                        quit_sig = 1;
                }

                SDL_SetRenderDrawColor(
                        gRenderer,
                        0xFF,
                        0xFF,
                        0xFF,
                        0xFF
                );

                SDL_RenderClear(gRenderer);

                // render filled red quad
                SDL_Rect fillRect = {
                    SCREEN_WIDTH / 4,
                    SCREEN_HEIGHT / 4,
                    SCREEN_WIDTH / 2,
                    SCREEN_HEIGHT / 2
                };

                SDL_SetRenderDrawColor(
                        gRenderer,
                        0xFF,
                        0x00,
                        0x00,
                        0xFF
                );

                SDL_RenderFillRect(gRenderer, &fillRect);

                // render green outlined quad
                SDL_Rect outlineRect = {
                    SCREEN_WIDTH / 6,
                    SCREEN_HEIGHT / 6,
                    SCREEN_WIDTH * 2 / 3,
                    SCREEN_HEIGHT * 2 / 3
                };

                SDL_SetRenderDrawColor(
                        gRenderer,
                        0x00,
                        0xFF,
                        0x00,
                        0xFF
                );

                SDL_RenderDrawRect(gRenderer, &outlineRect);

                // draw blue horizontal line
                SDL_SetRenderDrawColor(
                        gRenderer,
                        0x00,
                        0x00,
                        0xFF,
                        0xFF
                );

                SDL_RenderDrawLine(
                        gRenderer, 
                        0, 
                        SCREEN_HEIGHT / 2,
                        SCREEN_WIDTH,
                        SCREEN_HEIGHT / 2
                );

                // draw yellow vertical dotted line
                SDL_SetRenderDrawColor(
                        gRenderer,
                        0xFF,
                        0xFF,
                        0x00,
                        0xFF
                );

                int i = 0;
                for (i = 0; i < SCREEN_HEIGHT; i += 4)
                    SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);

                // update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    quit();
    return 0;
}

char init() {
    char success = 1;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not create window. SDL Error: %s\n", SDL_GetError());
        success = 0;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            printf("Warning: linear texture filetering not enabled.");

        gWindow = SDL_CreateWindow(
                "SDL tutorial",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN
        );

        if (gWindow == NULL) {
            printf("Could not create window. SDL Error: %s\n", SDL_GetError());
            success = 0;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(
                    gWindow,
                    -1,
                    SDL_RENDERER_ACCELERATED
            );
            if (gRenderer == NULL) {
                printf("Could not create renderer. SDL Error %s\n", SDL_GetError());
                success = 0;
            }
            else
            {
                SDL_SetRenderDrawColor(
                        gRenderer,
                        0xFF,
                        0xFF,
                        0xFF,
                        0xFF
                );

                // initialize PNG loading
                int imgFlags = IMG_INIT_PNG;

                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize. SDL_image Error: %s\n", IMG_GetError());
                    success = 0;
                }
            }
        }
    }

    return success;
}

char loadMedia() {
    char success = 1;
    return success;
}

SDL_Texture *loadTexture(char *path) {

    // final texture
    SDL_Texture *newTexture = NULL;

    // load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path);

    if (loadedSurface == NULL)
        printf("Unable to load image %s. SDL_image Error: %s\n", path, IMG_GetError());

    else
    {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        
        if (newTexture == NULL)
            printf("Unable to create texture from %s. SDL Error: %s\n", path, SDL_GetError());

        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

void quit() {

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    // destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}
