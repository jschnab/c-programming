// SDL tutorial 4 on lazyfoo.net
// optimization and stretching from tutorial 5 was added

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// original BMP images are 640 x 480 so we'll have to strech
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

// key press surfaces constants
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

// start SDL an create window
char init();

char loadMedia();

// free media and shut down SDL
void quit();

// load individual image
SDL_Surface *loadSurface(char *path);

// the window we render to
SDL_Window *gWindow = NULL;

// the surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// the images that correspond to a keypress
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

// current displayed image
SDL_Surface *gCurrentSurface = NULL;


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

            // set default current surface
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]; 
            
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

                    // user presses a key
                    else if (e.type == SDL_KEYDOWN)
                    {
                        // select surfaces based on key press
                        switch (e.key.keysym.sym)
                        {
                            case SDLK_UP:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                                break;

                            case SDLK_DOWN:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                                break;

                            case SDLK_LEFT:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                                break;

                            case SDLK_RIGHT:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                                break;

                            default:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                                break;
                        }
                    }
                }

                // apply the current image
                //SDL_BlitSurface(
                //        gCurrentSurface,
                //        NULL,
                //        gScreenSurface,
                //        NULL
                //);
                
                // apply the stretched image
                SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = SCREEN_WIDTH;
                stretchRect.h = SCREEN_HEIGHT;
                SDL_BlitScaled(
                        gCurrentSurface,
                        NULL,
                        gScreenSurface,
                        &stretchRect
                );

                // update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    quit();
    return 0;
}

SDL_Surface *loadSurface(char *path) {
    // the final optimized image
    SDL_Surface *optimizedSurface = NULL;

    // load image at specified path
    SDL_Surface *loadedSurface = SDL_LoadBMP(path);

    if (loadedSurface == NULL)
        printf("Unable to load image %s SDL Error: %s\n", path, SDL_GetError());

    else {
        optimizedSurface = SDL_ConvertSurface(
                loadedSurface,
                gScreenSurface->format,
                0
        );

        if (optimizedSurface == NULL)
            printf("Unable to optimized image %s. SDL Error: %s\n", path, SDL_GetError());

        // get rid of loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

char init() {
    // intitialization flag
    char success = 1;

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize. SDL Error: %s\n", SDL_GetError());
        success = 0;
    }
    else
    {
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
            printf("Window could not be created. SDL Error: %s\n", SDL_GetError());
            success = 1;
        }

        else
            // get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
    }

    return success;
}

char loadMedia() {
    // success flag
    char success = 1;

    // load default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("tuto4_img/press.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        printf("Failed to load default image.\n");
        success = 0;
    }

    // load up surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("tuto4_img/up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
        printf("Failed to load up image.\n");
        success = 0;
    }

    // load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("tuto4_img/down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
        printf("Failed to load down image.\n");
        success = 0;
    }

    // load left surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("tuto4_img/left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
        printf("Failed to load left image.\n");
        success = 0;
    }

    // load right surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("tuto4_img/right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        printf("Failed to load right image.\n");
        success = 0;
    }
    
    return success;
}

void quit() {
    // deallocate surfaces
    int i = 0;
    for (i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
        SDL_FreeSurface(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[i] = NULL;
    }

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}
