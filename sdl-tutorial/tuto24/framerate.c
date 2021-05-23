#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../debug.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

typedef struct ltexture {
    SDL_Texture *texture;
    int width;
    int height;
} LTexture;

typedef struct ltimer {
    uint32_t start_ticks;
    uint32_t pause_ticks;
    bool started;
    bool paused;
} LTimer;


void close_all();
bool initialize();
bool load_media();
void ltexture_destroy(LTexture *);
bool ltexture_from_text(LTexture *, char *, SDL_Color);
void ltexture_render(LTexture *, int x, int y, SDL_Rect *);
uint32_t ltimer_ticks(LTimer *);
void ltimer_start(LTimer *);
void ltimer_stop(LTimer *);
void ltimer_pause(LTimer *);
void ltimer_unpause(LTimer *);


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;
LTexture gFPSTexture = {NULL, 0, 0};


void close_all() {
    ltexture_destroy(&gFPSTexture);
    TTF_CloseFont(gFont);
    gFont = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


bool initialize() {
    check(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL failed to initialize: %s", SDL_GetError());
    check(
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"),
        "Linear texture filtering not enabled"
    );
    gWindow = SDL_CreateWindow(
        "SDL Tuto 24",
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
        "SDL_image failed to initialize: %s",
        IMG_GetError()
    );
    check(
        TTF_Init() == 0,
        "SDL_ttf failed to initialize: %s",
        TTF_GetError()
    );
    return true;

    error:
        return false;
}


bool load_media() {
    gFont = TTF_OpenFont("lazy.ttf", 28);
    check_mem(gFont);
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


bool ltexture_from_text(LTexture *t, char *text, SDL_Color text_color) {
    ltexture_destroy(t);
    SDL_Surface *text_surface = TTF_RenderText_Solid(gFont, text, text_color);
    check_mem(text_surface);
    t->texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);
    check_mem(t->texture);
    t->width = text_surface->w;
    t->height = text_surface->h;
    SDL_FreeSurface(text_surface);
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


void ltimer_start(LTimer *t) {
    t->started = true;
    t->paused = false;
    t->start_ticks = SDL_GetTicks();
    t->pause_ticks = 0;
}


void ltimer_stop(LTimer *t) {
    t->started = false;
    t->paused = false;
    t->start_ticks = 0;
    t->pause_ticks = 0;
}


void ltimer_pause(LTimer *t) {
    if (t->started && !t->paused) {
        t->paused = true;
        t->pause_ticks = SDL_GetTicks() - t->start_ticks;
        t->start_ticks = 0;
    }
}


void ltimer_unpause(LTimer *t) {
    if (t->started && t->paused) {
        t->paused = false;
        t->start_ticks = SDL_GetTicks() - t->pause_ticks;
        t->pause_ticks = 0;
    }
}


uint32_t ltimer_ticks(LTimer *t) {
    uint32_t time = 0;
    if (t->started) {
        if (t->paused) {
            time = t->pause_ticks;
        }
        else {
            time = SDL_GetTicks() - t->start_ticks;
        }
    }
    return time;
}


int main(int argc, char *argv[]) {
    check(initialize(), "Failed to initialize");
    check(load_media(), "Failed to load media");
    bool quit = false;
    SDL_Event e;
    SDL_Color text_color = {0, 0, 0, 255};
    LTimer fps_timer = {0, 0, false, false};
    char text[100];
    int counted_frames = 0;
    ltimer_start(&fps_timer);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        float avg_fps = counted_frames / (ltimer_ticks(&fps_timer) / 1000.0);
        if (avg_fps > 2000000) {
            avg_fps = 0;
        }
        sprintf(text, "Average frames per second: %.2f", avg_fps);
        check(
            ltexture_from_text(&gFPSTexture, text, text_color),
            "Failed to render FPS texture"
        );
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        ltexture_render(
            &gFPSTexture,
            (SCREEN_WIDTH - gFPSTexture.width) / 2,
            (SCREEN_HEIGHT - gFPSTexture.height) / 2,
            NULL
        );
        SDL_RenderPresent(gRenderer);
        counted_frames++;
    }
    close_all();
    return 0;

    error:
        close_all();
        return -1;
}
