// SDL tutorial 7 on lazyfoo.net
// texture rendering

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// load individual image as texture
SDL_Texture *loadTexture(char *path);

// the window we are rendering to
SDL_Window *gWindow = NULL;

// the window renderer
SDL_Renderer * gRenderer = NULL;

// currently displayed texture
SDL_Texture *gTexture = NULL;

char init();

char loadMedia();

void quit();

int main(int argc, char *argv[]) {

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

            while (!quit_sig) {
                
                while (SDL_PollEvent(&e) != 0) {

                    if (e.type == SDL_QUIT)
                        quit_sig = 1;
                }

                // clear screen
                SDL_RenderClear(gRenderer);

                // render texture to screen
                SDL_RenderCopy(
                        gRenderer,
                        gTexture,
                        NULL,
                        NULL
                );

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
            // create renderer for window
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
                // initialize renderer color
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
                    printf("Could not initialize SDL_image. SDL_image Error: %s\n", IMG_GetError());
                    success = 0;
                }
            }
        }
    }

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
        // create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        
        if (newTexture == NULL)
            printf("Unable to create texture from %s. SDL Error: %s\n", path, SDL_GetError());

        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

char loadMedia() {
    char success = 1;

    // load PNG texture
    gTexture = loadTexture("texture.png");
    if (gTexture == NULL) {
        printf("Failed to load texture image.\n");
        success = 0;
    }

    return success;
}

void quit() {
    // free loaded image
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    // destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}
