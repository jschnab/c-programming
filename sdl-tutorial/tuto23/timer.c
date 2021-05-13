#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "../debug.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

typedef struct LTexture {
    SDL_Texture *texture;
    int width;
    int height;
} LTexture;

typedef struct ltimer {
    uint32_t start_ticks;
    uint32_t pause_ticks;
    bool is_paused;
    bool is_started;
} LTimer;


void close_all();
bool initialize();
bool load_media();
void ltexture_destroy(LTexture *);
bool ltexture_from_text(LTexture *, char *, SDL_Color);
void ltexture_render(LTexture *, int, int, SDL_Rect *);
void ltimer_pause(LTimer *t);
void ltimer_unpause(LTimer *t);
void ltimer_start(LTimer *t);
void ltimer_stop(LTimer *t);
uint32_t ltimer_get_ticks(LTimer *t);


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;
LTexture gTimeTexture;
LTexture gPauseTexture;
LTexture gStartTexture;


void close_all() {
    ltexture_destroy(&gTimeTexture);
    ltexture_destroy(&gPauseTexture);
    ltexture_destroy(&gStartTexture);
    TTF_CloseFont(gFont);
    gFont = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


bool initialize() {
    check(
        SDL_Init(SDL_INIT_VIDEO) == 0,
        "SDL failed to initialize: %s",
        SDL_GetError()
    );
    check(
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"),
        "Linear texture filtering not enabled"
    );
    gWindow = SDL_CreateWindow(
        "SDL Tuto 23",
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
    check(
        gFont != NULL,
        "Failed to load 'lazy.ttf': %s",
        TTF_GetError()
    );
    SDL_Color text_color = {0, 0, 0, 255};
    check(
        ltexture_from_text(
            &gStartTexture,
            "Press 'S' to start or stop the timer",
            text_color
        ),
        "Failed to render start/stop prompt texture"
    );
    check(
        ltexture_from_text(
            &gPauseTexture,
            "Press 'P' to pause or unpause the timer",
            text_color
        ),
        "Failed to render pause/unpause prompt texture"
    );
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
    check(
        text_surface != NULL,
        "Failed to render text surface: %s",
        TTF_GetError()
    );
    t->texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);
    check(
        t->texture != NULL,
        "Failed to create texture from text: %s",
        SDL_GetError()
    );
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
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, t->texture, clip, &render_quad);
}


void ltimer_unpause(LTimer *t) {
    if (t->is_started && t->is_paused) {
        t->is_paused = false;
        t->start_ticks = SDL_GetTicks() - t->pause_ticks;
        t->pause_ticks = 0;
    }
}


void ltimer_pause(LTimer *t) {
    if (t->is_started && !t->is_paused) {
        t->is_paused = true;
        t->pause_ticks = SDL_GetTicks() - t->start_ticks;
        t->start_ticks = 0;
    }
}


void ltimer_start(LTimer *t) {
    t->is_started = true;
    t->is_paused = false;
    t->start_ticks = SDL_GetTicks();
    t->pause_ticks = 0;
}


void ltimer_stop(LTimer *t) {
    t->is_started = false;
    t->is_paused = false;
    t->start_ticks = 0;
    t->pause_ticks = 0;
}


uint32_t ltimer_get_ticks(LTimer *t) {
    uint32_t time = 0;
    if (t->is_started) {
        if (t->is_paused) {
            return t->pause_ticks;
        }
        time = SDL_GetTicks() - t->start_ticks;
    }
    return time;
}


int main(int argc, char *argv[]) {
    check(initialize(), "Failed to initialize");
    check(load_media(), "Failed to load media");
    bool quit = false;
    SDL_Event e;
    SDL_Color text_color = {0, 0, 0, 255};
    LTimer timer = {0, 0, false, false};
    char time_text[100];
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_s) {
                    if (timer.is_started) {
                        ltimer_stop(&timer);
                    }
                    else {
                        ltimer_start(&timer);
                    }
                }
                else if (e.key.keysym.sym == SDLK_p) {
                    if (timer.is_paused && timer.is_started) {
                        ltimer_unpause(&timer);
                    }
                    else {
                        ltimer_pause(&timer);
                    }
                }
            }
        }
        sprintf(
            time_text,
            "Seconds since start time %.3f",
            ltimer_get_ticks(&timer) / 1000.f
        );
        check(
            ltexture_from_text(
                &gTimeTexture,
                time_text,
                text_color
            ),
            "Failed to render time texture"
        );
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        ltexture_render(
            &gStartTexture,
            (SCREEN_WIDTH - gStartTexture.width) / 2,
            0,
            NULL
        );
        ltexture_render(
            &gPauseTexture,
            (SCREEN_WIDTH - gPauseTexture.width) / 2,
            gStartTexture.height,
            NULL
        );
        ltexture_render(
            &gTimeTexture,
            (SCREEN_WIDTH - gTimeTexture.width) / 2,
            (SCREEN_HEIGHT - gTimeTexture.height) / 2,
            NULL
        );
        SDL_RenderPresent(gRenderer);
    }
    close_all();
    return 0;

    error:
        return -1;
}
