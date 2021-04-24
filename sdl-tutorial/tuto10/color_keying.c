#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


typedef struct ltexture {
    SDL_Texture *texture;
    int width;
    int height;
} LTexture;


bool initialize();
bool load_media();
void close_all();


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
LTexture foreground = {NULL, 0, 0};
LTexture background = {NULL, 0, 0};


bool load_file(LTexture *t, char *path) {
    bool success = true;
    SDL_Texture *final_texture = NULL;
    SDL_Surface *loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        fprintf(stderr, "Unable to load image '%s': %s\n", path, IMG_GetError());
        success = false;
    }
    else {
        /* color key image */
        SDL_SetColorKey(
            loaded_surface,
            SDL_TRUE,
            SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF)
        );
        final_texture = SDL_CreateTextureFromSurface(gRenderer, loaded_surface);
        if (final_texture == NULL) {
            fprintf(stderr, "Unable to create texture from '%s': %s\n", path, SDL_GetError());
            success = false;
        }
        else {
            t->width = loaded_surface->w;
            t->height = loaded_surface->h;
        }
        SDL_FreeSurface(loaded_surface);
    }
    t->texture = final_texture;
    return success;
}


void texture_free(LTexture *t) {
    SDL_DestroyTexture(t->texture);
    t->texture = NULL;
    t->width = 0;
    t->height = 0;
}


void texture_render(LTexture *t, int x1, int x2, int y1, int y2) {
    SDL_Rect render_quad = {x1, y1, x2, y2};
    SDL_RenderCopy(gRenderer, t->texture, NULL, &render_quad);
}


bool initialize() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize: %s\n", SDL_GetError());
        success = false;
    }
    else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            fprintf(stderr, "Linear texture filtering not enabeld\n");
        }
        gWindow = SDL_CreateWindow(
            "SDL Tuto 10",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0
        );
        if (gWindow == NULL) {
            fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int img_flags = IMG_INIT_PNG;
                if (!(IMG_Init(img_flags) & img_flags)) {
                    fprintf(stderr, "SDL_image could not initialize: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}


bool load_media() {
    bool success = true;
    if (!load_file(&foreground, "foreground.png")) {
        fprintf(stderr, "Failed to load foreground texture image\n");
        success = false;
    }
    if (!load_file(&background, "background.png")) {
        fprintf(stderr, "Failed to load background texture image\n");
        success = false;
    }
    return success;
}


void close_all() {
    texture_free(&foreground);
    texture_free(&background);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char *argv[]) {
    if (initialize()) {
        if (load_media()) {
            bool quit = false;
            SDL_Event e;
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                texture_render(&background, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
                texture_render(&foreground, 240, foreground.width, 190, foreground.height);
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    close_all();
    return 0;
}
