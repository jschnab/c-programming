#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../debug.h"

#define SCREEN_FPS 60
#define SCREEN_TICK_PER_FRAME (1000 / SCREEN_FPS)


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int DOT_WIDTH = 20;
const int DOT_HEIGHT = 20;
const int DOT_VEL = 10;


typedef struct ltexture {
    SDL_Texture *texture;
    int width;
    int height;
} LTexture;


typedef struct dot {
    int pos_x;
    int pos_y;
    int vel_x;
    int vel_y;
} Dot;


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
bool ltexture_from_file(LTexture *, char *);
void ltexture_render(LTexture *, int, int, SDL_Rect *);
uint32_t ltimer_get_ticks(LTimer *);
void ltimer_start(LTimer *);
void ltimer_stop(LTimer *);
void ltimer_pause(LTimer *);
void ltimer_unpause(LTimer *);
void dot_handle_event(Dot *, SDL_Event);
void dot_move(Dot *);


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
LTexture gDotTexture = {NULL, 0, 0};


void close_all() {
    ltexture_destroy(&gDotTexture);
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    IMG_Quit();
    SDL_Quit();
}


bool initialize() {
    check(
        SDL_Init(SDL_INIT_VIDEO) == 0,
        "SDL failed to initialize: %s",
        SDL_GetError()
    );
    check_debug(
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"),
        "Linear texture filtering not enabled"
    );
    gWindow = SDL_CreateWindow(
        "SDL Tuto 26",
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
    return true;

    error:
        return false;
}


bool load_media() {
    check(ltexture_from_file(&gDotTexture, "dot.bmp"), "Failed to load dot texture");
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


bool ltexture_from_file(LTexture *t, char *path) {
    ltexture_destroy(t);
    SDL_Surface *loaded_surface = IMG_Load(path);
    check_mem(loaded_surface);
    SDL_SetColorKey(
        loaded_surface,
        SDL_TRUE,
        SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF)
    );
    t->texture = SDL_CreateTextureFromSurface(gRenderer, loaded_surface);
    check_mem(t->texture);
    t->width = loaded_surface->w;
    t->height = loaded_surface->h;
    SDL_FreeSurface(loaded_surface);
    return true;

    error:
        SDL_FreeSurface(loaded_surface);
        return false;
}


void ltexture_render(LTexture *t, int x, int y, SDL_Rect *clip) {
    SDL_Rect render_quad = {x, y, t->width, t->height};
    if (clip != NULL) {
        render_quad.w = clip->w;
        render_quad.h = clip->w;
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


void dot_handle_event(Dot *dot, SDL_Event event) {
    /* key is pressed */
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch(event.key.keysym.sym) {
            case SDLK_UP:
                dot->vel_y -= DOT_VEL;
                break;
            case SDLK_DOWN:
                dot->vel_y += DOT_VEL;
                break;
            case SDLK_LEFT:
                dot->vel_x -= DOT_VEL;
                break;
            case SDLK_RIGHT:
                dot->vel_x += DOT_VEL;
                break;
        }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
    /* key is released */
        switch(event.key.keysym.sym) {
            case SDLK_UP:
                dot->vel_y += DOT_VEL;
                break;
            case SDLK_DOWN:
                dot->vel_y -= DOT_VEL;
                break;
            case SDLK_LEFT:
                dot->vel_x += DOT_VEL;
                break;
            case SDLK_RIGHT:
                dot->vel_x -= DOT_VEL;
                break;
        }
    }
}


void dot_move(Dot *dot) {
    dot->pos_x += dot->vel_x;
    if ((dot->pos_x < 0) || (dot->pos_x + DOT_WIDTH > SCREEN_WIDTH)) {
        dot->pos_x -= dot->vel_x;
    }
    dot->pos_y += dot->vel_y;
    if ((dot->pos_y < 0) || (dot->pos_y + DOT_HEIGHT > SCREEN_HEIGHT)) {
        dot->pos_y -= dot->vel_y;
    }
}


int main(int argc, char *argv[]) {
    check(initialize(), "Failed to initialize");
    check(load_media(), "Failed to load media");
    bool quit = false;
    SDL_Event e;
    Dot dot = {0, 0, 0, 0};
    LTimer fps_timer;
    LTimer cap_timer;
    ltimer_start(&fps_timer);
    while (!quit) {
        ltimer_start(&cap_timer);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            dot_handle_event(&dot, e);
        }
        dot_move(&dot);
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        ltexture_render(&gDotTexture, dot.pos_x, dot.pos_y, NULL);        
        SDL_RenderPresent(gRenderer);
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
