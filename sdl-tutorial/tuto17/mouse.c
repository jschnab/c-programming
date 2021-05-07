#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../debug.h"

#define TOTAL_BUTTONS 4
#define BUTTON_SPRITE_TOTAL 4


const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;


enum ButtonSprite {
    BUTTON_SPRITE_MOUSE_OUT,
    BUTTON_SPRITE_MOUSE_OVER_MOTION,
    BUTTON_SPRITE_MOUSE_DOWN,
    BUTTON_SPRITE_MOUSE_UP
};


typedef struct ltexture {
    SDL_Texture *texture;
    int width;
    int height;
} LTexture;


typedef struct lbutton {
    SDL_Point position;
    int current_sprite;
} LButton;


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
LTexture gButtonSpriteSheetTexture = {NULL, 0, 0};
LButton gButtons[TOTAL_BUTTONS];


void close_all();
bool initialize();
bool load_media();
void ltexture_destroy(LTexture *);
bool ltexture_from_file(LTexture *, char *);
void ltexture_render(LTexture *, int, int, SDL_Rect *);
void lbutton_handle_event(LButton *, SDL_Event *);
void lbutton_render(LButton);
void lbutton_set_position(LButton *, int, int);


void ltexture_destroy(LTexture *t) {
    if (t->texture != NULL) {
        SDL_DestroyTexture(t->texture);
        t->texture = NULL;
        t->width = 0;
        t->height = 0;
    }
}


bool ltexture_from_file(LTexture *t, char *path) {
    ltexture_destroy(t);
    SDL_Surface *loaded_surface = NULL;
    loaded_surface = IMG_Load(path);
    check(loaded_surface, "Failed to load image '%s': %s", path, IMG_GetError());
    SDL_SetColorKey(
        loaded_surface,
        SDL_TRUE,
        SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF)
    );
    SDL_Texture *final_texture = NULL;
    final_texture = SDL_CreateTextureFromSurface(gRenderer, loaded_surface);
    check(final_texture, "Failed to create texture from '%s': %s", path, SDL_GetError());
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
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, t->texture, clip, &render_quad);
}


void lbutton_set_position(LButton *button, int x, int y) {
    button->position.x = x;
    button->position.y = y;
}


void lbutton_handle_event(LButton *button, SDL_Event *e) {
    if (
        e->type == SDL_MOUSEMOTION ||
        e->type == SDL_MOUSEBUTTONDOWN ||
        e->type == SDL_MOUSEBUTTONUP
    ) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        /* check if mouse is in button */
        bool inside = true;
        if (x < button->position.x) { inside = false; }
        else if (x > button->position.x + BUTTON_WIDTH) { inside = false; }
        else if (y < button->position.y) { inside = false; }
        else if (y > button->position.y + BUTTON_HEIGHT) { inside = false; }
        if (!inside) {
            button->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        else {
            switch (e->type) {
                case SDL_MOUSEMOTION:
                    button->current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    button->current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                case SDL_MOUSEBUTTONUP:
                    button->current_sprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}


void lbutton_render(LButton button) {
    ltexture_render(
        &gButtonSpriteSheetTexture,
        button.position.x,
        button.position.y,
        &gSpriteClips[button.current_sprite]
    );
}


bool initialize() {
    check(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL failed to initialize: %s", SDL_GetError());
    check(
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_TRUE,
        "Linear texture filtering is not enabled"
    );
    gWindow = SDL_CreateWindow(
        "SDL Tuto 17",
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
    check(
        ltexture_from_file(&gButtonSpriteSheetTexture, "button2.png"),
        "Failed to load button sprite texture"
    );
    for (int i = 0; i < BUTTON_SPRITE_TOTAL; i++) {
        gSpriteClips[i].x = 0;
        gSpriteClips[i].y = i * 200;
        gSpriteClips[i].w = BUTTON_WIDTH;
        gSpriteClips[i].h = BUTTON_HEIGHT;
    }
    lbutton_set_position(&gButtons[0], 0, 0);
    lbutton_set_position(&gButtons[1], SCREEN_WIDTH - BUTTON_WIDTH, 0);
    lbutton_set_position(&gButtons[2], 0, SCREEN_HEIGHT - BUTTON_HEIGHT);
    lbutton_set_position(
        &gButtons[3],
        SCREEN_WIDTH - BUTTON_WIDTH,
        SCREEN_HEIGHT - BUTTON_HEIGHT
    );

    for (int i = 0; i < TOTAL_BUTTONS; i++) {
    gButtons[i].current_sprite = BUTTON_SPRITE_MOUSE_OUT;
    }
    return true;

    error:
        return false;
}


void close_all() {
    ltexture_destroy(&gButtonSpriteSheetTexture);
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char *argv[]) {
    check(initialize(), "Failed to initialize");
    check(load_media(), "Failed to load media");
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            for (int i = 0; i < TOTAL_BUTTONS; i++) {
                lbutton_handle_event(&gButtons[i], &e);
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        for (int i = 0; i < TOTAL_BUTTONS; i++) {
            lbutton_render(gButtons[i]);
        }
        SDL_RenderPresent(gRenderer);
    }
    close_all();
    return 0;

    error:
        close_all();
}
