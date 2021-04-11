// tutorial 10 of lazyfoo.net

#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 280;

class LTexture {
    public:
        // initializes variables
        LTexture();

        // deallocates memory
        ~LTexture();

        // loads image at specified path
        bool loadFromFile(std::string path);

        // deallocates texture
        void free();

        // renders texture at given point
        void render(int x, int y);

        // gets image dimensions
        int getWidth();
        int getHeight();

    private:
        // the hardware texture
        SDL_Texture *mTexture;

        // image dimensions
        int mWidth;
        int mHeight;
};

bool init();

bool loadMedia();

void close();

SDL_Window *gWindow = NULL;

SDL_Renderer *gRenderer = NULL;

// scene textures
LTexture gForeground;
LTexture gBackground;

LTexture::LTexture() {
    // initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture() {
    // deallocate
    free();
}

bool LTexture::loadFromFile(std::string path) {
    // get rid of pre-existing texture
    free();

    // final texture
    SDL_Texture *newTexture = NULL;

    // load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
        printf(
                "Unable to load image %s. SDL_image Error: %s\n",
                path.c_str(),
                IMG_GetError()
        );

    else {
        // color key image
        SDL_SetColorKey(
                loadedSurface,
                SDL_TRUE,
                SDL_MapRGB(
                    loadedSurface->format,
                    0,
                    0xFF,
                    0xFF
                )
        );

        // create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if (newTexture == NULL)
            printf(
                    "Unable to create texture from %s. SDL Error: %s\n",
                    path.c_str(),
                    SDL_GetError()
            );

        else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    // return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free() {
    // free texture if it exists
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(int x, int y) {
    // set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth() {
    return mWidth;
}

int LTexture::getHeight() {
    return mHeight;
}

bool init() {
    // initialization flat
    bool success = true;

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize. SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    else {
        // set texture filetering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            printf("Warning: linear texture filetering not enables.");

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
            printf("Unable to create window. SDL Error: %s\n", SDL_GetError());
            success = false;
        }

        else {
            // create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

            if (gRenderer == NULL) {
                printf("Renderer could not be created. SDL Error: %s\n", SDL_GetError());
                success = false;
            }

            else {
                // initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf(
                            "SDL_image could not initialize. SDL_image Error: %s\n",
                            IMG_GetError()
                    );
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia() {
    // flag for loading success
    bool success = true;

    // load foreground texture
    if (!gForeground.loadFromFile("mercury.png")) {
        printf("Failed to load foreground texture image\n");
        success = false;
    }

    // load background texture
    if (!gBackground.loadFromFile("space_background.png")) {
        printf("Failed to load background image\n");
        success = false;
    }
    
    return success;
}

void close() {
    // free loaded images
    gForeground.free();
    gBackground.free();

    // destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    // start up SDL and create window
    if (!init())
        printf("Failed to initialize.\n");

    else {
        // load media
        if (!loadMedia())
            printf("Failed to load media.\n");

        else {
            // main loop flag
            bool quit = false;

            // event handler
            SDL_Event e;

            // while application is running
            while (!quit) {
                // handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT)
                        quit = true;
                }

                // clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                gBackground.render(0, 0);
                gForeground.render(40, 40);

                SDL_RenderPresent(gRenderer);
            }
        }
    }

    close();
    return 0;
}
