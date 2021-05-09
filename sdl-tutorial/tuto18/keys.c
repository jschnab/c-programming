#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "../debug.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


typedef struct ltexture {
    SDL_Texture *texture;
    int width;
    int height;
} LTexture;


void close_all();
bool initialize();
bool load_media();
void ltexture_destroy(LTexture *);
bool ltexture_from_file(LTexture *, char *);
void ltexture_render(LTexture *, int, int, SDL_Rect *);


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
LTexture gPressTexture = {NULL, 0, 0};
LTexture gUpTexture = {NULL, 0, 0};
LTexture gDownTexture = {NULL, 0, 0};
LTexture gLeftTexture = {NULL, 0, 0};
LTexture gRightTexture = {NULL, 0, 0};


void close_all() {
    ltexture_destroy(&gPressTexture);
    ltexture_destroy(&gUpTexture);
    ltexture_destroy(&gDownTexture);
    ltexture_destroy(&gLeftTexture);
    ltexture_destroy(&gRightTexture);
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    IMG_Quit();
    SDL_Quit();
}


bool initialize() {
    check(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL could not initialize: %s", SDL_GetError());
    check(
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"),
        "Linear texture filtering not enabled"
    );
    gWindow = SDL_CreateWindow(
        "SDL Tuto 18",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );
    check_mem(gWindow);
    gRenderer = SDL_CreateRenderer(
        gWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    check_mem(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int img_flags = IMG_INIT_PNG;
    check(
        IMG_Init(img_flags) & img_flags,
        "SDL_image could not initialize: %s",
        IMG_GetError()
    );
    return true;

    error:
        return false;
}


bool load_media() {
    check(ltexture_from_file(&gPressTexture, "press.png"), "Failed to load 'press.png'");
    check(ltexture_from_file(&gUpTexture, "up.png"), "Failed to load 'up.png'");
    check(ltexture_from_file(&gDownTexture, "down.png"), "Failed to load 'down.png'");
    check(ltexture_from_file(&gLeftTexture, "left.png"), "Failed to load 'left.png'");
    check(ltexture_from_file(&gRightTexture, "right.png"), "Failed to load 'right.png'");
    return true;

    error:
        return false;
}


void ltexture_destroy(LTexture *t) {
    if (t->texture != NULL) {
        SDL_DestroyTexture(t->texture);
        t->width = 0;
        t->height = 0;
    }
}


bool ltexture_from_file(LTexture *t, char *path) {
    SDL_Surface *loaded_surface = IMG_Load(path);
    check_mem(loaded_surface);
    SDL_SetColorKey(
        loaded_surface,
        SDL_TRUE,
        SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF)
    );
    SDL_Texture *final_texture = NULL;
    final_texture = SDL_CreateTextureFromSurface(gRenderer, loaded_surface);
    check_mem(final_texture);
    t->texture = final_texture;
    t->width = loaded_surface->w;
    t->height = loaded_surface->h;
    SDL_FreeSurface(loaded_surface);
    return true;

    error:
        return false;
}


void ltexture_render(LTexture *t, int x, int y, SDL_Rect *clip) {
    SDL_Rect render_quad = {x, y, t->width, t->height};
    if (clip != NULL) {
        render_quad.x = clip->w;
        render_quad.y = clip->h;
    }
    SDL_RenderCopy(gRenderer, t->texture, clip, &render_quad);
}


int main(int argc, char *argv[]) {
    check(initialize(), "Failed to initialize");
    check(load_media(), "Failed to load media");
    bool quit = false;
    SDL_Event e;
    LTexture *current_texture = NULL;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        const uint8_t *key_states = SDL_GetKeyboardState(NULL);
        if (key_states[SDL_SCANCODE_UP]) {
            current_texture = &gUpTexture;
        }
        else if (key_states[SDL_SCANCODE_DOWN]) {
            current_texture = &gDownTexture;
        }
        else if (key_states[SDL_SCANCODE_LEFT]) {
            current_texture = &gLeftTexture;
        }
        else if (key_states[SDL_SCANCODE_RIGHT]) {
            current_texture = &gRightTexture;
        }
        else {
            current_texture = &gPressTexture;
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        ltexture_render(current_texture, 0, 0, NULL);
        SDL_RenderPresent(gRenderer);
    }
    close_all();
    return 0;

    error:
        return -1;
}
