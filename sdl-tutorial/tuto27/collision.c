#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../debug.h"

#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME (1000 / SCREEN_FPS)


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
    int posx;
    int posy;
    int velx;
    int vely;
    SDL_Rect collider;
} Dot;

typedef struct ltimer {
    uint32_t start_ticks;
    uint32_t pause_ticks;
    bool started;
    bool paused;
} LTimer;


bool check_collision(SDL_Rect, SDL_Rect);
void close_all();
void dot_handle_event(Dot *, SDL_Event);
void dot_move(Dot *, SDL_Rect);
void dot_render(Dot *);
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


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
LTexture gDotTexture = {NULL, 0, 0};


bool check_collision(SDL_Rect a, SDL_Rect b) {
    int left_a, left_b, right_a, right_b, top_a, top_b, bottom_a, bottom_b;

    /* a collision box */
    left_a = a.x;
    right_a = a.x + a.w;
    top_a = a.y;
    bottom_a = a.y + a.h;

    /* b collision box */
    left_b = b.x;
    right_b = b.x + b.w;
    top_b = b.y;
    bottom_b = b.y + b.h;

    if (bottom_a <= top_b) {
        return false;
    }
    if (top_a >= bottom_b) {
        return false;
    }
    if (right_a <= left_b) {
        return false;
    }
    if (left_a >= right_b) {
        return false;
    }
    return true;
}


void close_all() {
    ltexture_destroy(&gDotTexture);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}


void dot_handle_event(Dot *d, SDL_Event e) {
    /* key was pressed */
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                d->vely -= DOT_VEL;
                break;
            case SDLK_DOWN:
                d->vely += DOT_VEL;
                break;
            case SDLK_LEFT:
                d->velx -= DOT_VEL;
                break;
            case SDLK_RIGHT:
                d->velx += DOT_VEL;
                break;
        }
    }

    /* key was released */
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                d->vely += DOT_VEL;
                break;
            case SDLK_DOWN:
                d->vely -= DOT_VEL;
                break;
            case SDLK_LEFT:
                d->velx += DOT_VEL;
                break;
            case SDLK_RIGHT:
                d->velx -= DOT_VEL;
                break;
        }
    }
}


void dot_move(Dot *d, SDL_Rect wall) {
    /* move dot left or right */
    d->posx += d->velx;
    d->collider.x = d->posx;

    /* if the dot collided or went too far to the left or right */
    if (
        (d->posx < 0) ||
        (d->posx + DOT_WIDTH > SCREEN_WIDTH) ||
        check_collision(d->collider, wall)
    ) {
        d->posx -= d->velx;
        d->collider.x = d->posx;
    }

    /* move dot up or down */
    d->posy += d->vely;
    d->collider.y = d->posy;

    /* if the dot collided or went too far up or down */
    if (
        (d->posy < 0) ||
        (d->posy + DOT_HEIGHT > SCREEN_HEIGHT) ||
        check_collision(d->collider, wall)
    ) {
        d->posy -= d->vely;
        d->collider.y = d->posy;
    }
}


bool initialize() {
    check(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL failed to initialize: %s", SDL_GetError());
    check_debug(
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"),
        "Linear texture filtering not enabled"
    );
    gWindow = SDL_CreateWindow(
        "SDL Tuto 27",
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
    Dot dot = {
        0,
        0,
        0,
        0,
        {0, 0, DOT_WIDTH, DOT_HEIGHT}
    };
    SDL_Rect wall = {300, 40, 40, 400};
    LTimer cap_timer;

    while (!quit) {
        ltimer_start(&cap_timer);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            dot_handle_event(&dot, e);
        }
        dot_move(&dot, wall);

        /* clear screen */
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        /* draw wall */
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawRect(gRenderer, &wall);

        ltexture_render(&gDotTexture, dot.posx, dot.posy, NULL);

        SDL_RenderPresent(gRenderer);

        /* cap frame rate */
        int frame_ticks = ltimer_get_ticks(&cap_timer);
        if (frame_ticks < SCREEN_TICKS_PER_FRAME) {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
        }
    }

    close_all();
    return 0;

    error:
        close_all();
        return -1;
}
