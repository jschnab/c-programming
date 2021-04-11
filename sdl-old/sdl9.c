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

SDL_Texture *gTexture = NULL;

int main(int argc, char *argv[]) {

    if (!init()) {
        printf("Failed to initialize.\n");
    }
    else
    {
        if (!loadMedia()) {
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

                // top left corner viewport
                SDL_Rect topLeftViewport;
                topLeftViewport.x = 0;
                topLeftViewport.y = 0;
                topLeftViewport.w = SCREEN_WIDTH / 2;
                topLeftViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(gRenderer, &topLeftViewport);

                // render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                // top right viewport
                SDL_Rect topRightViewport;
                topRightViewport.x = SCREEN_WIDTH / 2;
                topRightViewport.y = 0;
                topRightViewport.w = SCREEN_WIDTH / 2;
                topRightViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(gRenderer, &topRightViewport);

                // render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                // bottom viewport
                SDL_Rect bottomViewport;
                bottomViewport.x = 0;
                bottomViewport.y = SCREEN_HEIGHT / 2;
                bottomViewport.w = SCREEN_WIDTH;
                bottomViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(gRenderer, &bottomViewport);

                // render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

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

char loadMedia() {
    char success = 1;

    gTexture = loadTexture("viewport.png");

    if (gTexture == NULL) {
        printf("Failed to load texture image.\n");
        success = 0;
    }

    return success;
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
