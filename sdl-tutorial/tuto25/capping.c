#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../debug.h"

#define SCREEN_FPS 60
#define SCREEN_TICK_PER_FRAME (1000 / SCREEN_FPS)

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
void ltexture_render(LTexture *, int, int, SDL_Rect *);
uint32_t ltimer_get_ticks(LTimer *);
void ltimer_start(LTimer *);
void ltimer_stop(LTimer *);
void ltimer_pause(LTimer *);
void ltimer_unpause(LTimer *);


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;
LTexture gFPSTexture;


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
    check(SDL_Init(SDL_INIT_VIDEO) == 0, "Failed to initialize SDL: %s", SDL_GetError());
    check(
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"),
        "Linear texture filtering not enabled"
    );
    gWindow = SDL_CreateWindow(
        "SDL Tuto 25",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );
    check_mem(gWindow);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    check_mem(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int img_flags = IMG_INIT_PNG;
    check(
        IMG_Init(img_flags) & img_flags,
        "Failed to initialize SDL_image: %s",
        IMG_GetError()
    );
    check(TTF_Init() == 0, "Failed to initialize SDL_ttf: %s", TTF_GetError());
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
        t->texture = NULL;
        t->width = 0;
        t->height = 0;
    }
}


bool ltexture_from_text(LTexture *t, char *text, SDL_Color color) {
    ltexture_destroy(t);
    SDL_Surface *text_surface = TTF_RenderText_Solid(gFont, text, color);
    check_mem(text_surface);
    t->texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);
    check_mem(t->texture);
    t->width = text_surface->w;
    t->height = text_surface->h;
    SDL_FreeSurface(text_surface);
    return true;

    error:
        SDL_FreeSurface(text_surface);
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


uint32_t ltimer_get_ticks(LTimer *t) {
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


int main(int argc, char *argv[]) {
    check(initialize(), "Failed to initialize");
    check(load_media(), "Failed to load media");
    bool quit = false;
    SDL_Event e;
    char time_text[100];
    SDL_Color text_color = {0, 0, 0, 255};
    LTimer fps_timer;
    LTimer cap_timer;
    int counted_frames = 0;
    ltimer_start(&fps_timer);
    while (!quit) {
        ltimer_start(&cap_timer);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        float avg_fps = counted_frames / (ltimer_get_ticks(&fps_timer) / 1000.f);
        if (avg_fps > 2000000) {
            avg_fps = 0;
        }
        sprintf(time_text, "Average frames per second (capped): %f", avg_fps);
        check(
            ltexture_from_text(&gFPSTexture, time_text, text_color),
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
        int frame_ticks = ltimer_get_ticks(&cap_timer);
        if (frame_ticks < SCREEN_TICK_PER_FRAME) {
            SDL_Delay(SCREEN_TICK_PER_FRAME - frame_ticks);
        }
    }
    close_all();
    return 0;

    error:
        close_all();
        return -1;
}
