#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../debug.h"


#define N_COLLIDERS 11
#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME (1000 / SCREEN_FPS)


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int DOT_WIDTH = 20;
const int DOT_HEIGHT = 20;
const int DOT_VEL = 1;


typedef struct ltexture {
    SDL_Texture *texture;
    int width;
    int height;
} LTexture;


typedef struct dot {
    int posx, posy, velx, vely;
    SDL_Rect *colliders;
} Dot;


typedef struct ltimer {
    uint32_t start_ticks;
    uint32_t pause_ticks;
    bool started;
    bool paused;
} LTimer;


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
LTexture gDotTexture;


bool check_collision(SDL_Rect *, SDL_Rect *);
void close_all();
void dot_handle_event(Dot *, SDL_Event);
void dot_move(Dot *, SDL_Rect *);
void dot_render(Dot *);
void dot_shift_colliders(Dot *);
bool initialize();
bool load_media();
void ltexture_destroy(LTexture *);
bool ltexture_from_file(LTexture *, char *path);
void ltexture_render(LTexture *, int, int, SDL_Rect *);
uint32_t ltimer_get_ticks(LTimer *);
void ltimer_start(LTimer *);
void ltimer_stop(LTimer *);


bool check_collision(SDL_Rect *a, SDL_Rect *b) {
    int left_a, right_a, top_a, bottom_a;
    int left_b, right_b, top_b, bottom_b;

    for (int box = 0; box < N_COLLIDERS; box++) {
        left_a = a[box].x;
        right_a = a[box].x + a[box].w;
        top_a = a[box].y;
        bottom_a = a[box].y + a[box].h;

        for (int box = 0; box < N_COLLIDERS; box++) {
            left_b = b[box].x;
            right_b = b[box].x + b[box].w;
            top_b = b[box].y;
            bottom_b = b[box].y + b[box].h;

            /* if any side of A is inside of B, collision is detected */
            if (
                (
                    bottom_a <= top_b ||
                    top_a >= bottom_b ||
                    right_a <= left_b ||
                    left_a >= right_b
                ) == false
            ) {
                return true;
            }
        }
    }

    return false;
}


void close_all() {
    ltexture_destroy(&gDotTexture);
    SDL_DestroyRenderer(gRenderer);
    gWindow = NULL;
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}


void dot_handle_event(Dot *dot, SDL_Event e) {
    /* if a key was pressed */
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        /* adjust the velocity */
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                dot->vely -= DOT_VEL;
                break;
            case SDLK_DOWN:
                dot->vely += DOT_VEL;
                break;
            case SDLK_LEFT:
                dot->velx -= DOT_VEL;
                break;
            case SDLK_RIGHT:
                dot->velx += DOT_VEL;
                break;
        }
    }

    /* if a key was released */
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                dot->vely += DOT_VEL;
                break;
            case SDLK_DOWN:
                dot->vely -= DOT_VEL;
                break;
            case SDLK_LEFT:
                dot->velx += DOT_VEL;
                break;
            case SDLK_RIGHT:
                dot->velx -= DOT_VEL;
                break;
        }
    }
}


void dot_move(Dot *dot, SDL_Rect *other_colliders) {
    /* move the dot left or right */
    dot->posx += dot->velx;
    dot_shift_colliders(dot);

    /* if the dot collided or went too far left or right, move back */
    if ((
        dot->posx < 0 ||
        dot->posx + DOT_WIDTH > SCREEN_WIDTH ||
        check_collision(dot->colliders, other_colliders)
    )) {
        dot->posx -= dot->velx;
        dot_shift_colliders(dot);
    }

    /* move the dot up or down */
    dot->posy += dot->vely;
    dot_shift_colliders(dot);
    
    /* if the dot collided or went too far up or down, move back */
    if ((
        dot->posy < 0 ||
        dot->posy + DOT_HEIGHT > SCREEN_HEIGHT ||
        check_collision(dot->colliders, other_colliders)
    )) {
        dot->posy -= dot->vely;
        dot_shift_colliders(dot);
    }
}


void dot_render(Dot *dot) {
    ltexture_render(&gDotTexture, dot->posx, dot->posy, NULL);
}


void dot_shift_colliders(Dot *dot) {
    /* the row offset */
    int r = 0;

    /* go through the dot's collision boxes */
    for (int set = 0; set < N_COLLIDERS; set++) {
        /* center the collision box */
        dot->colliders[set].x = dot->posx + (DOT_WIDTH - dot->colliders[set].w) / 2;
        /* set the collision box at its row offset */
        dot->colliders[set].y = dot->posy + r;
        /* move the row offset down the height of the collision boxes */
        r += dot->colliders[set].h;
    }
}


bool initialize() {
    check(
        SDL_Init(SDL_INIT_VIDEO) == 0,
        "Failed to initialize SDL: %s",
        SDL_GetError()
    );
    check(
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"),
        "Linear texture filtering not enabled."
    );
    gWindow = SDL_CreateWindow(
        "SDL Tuto 28",
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
        "Failed to initialize SDL_image: %s",
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
        render_quad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, t->texture, clip, &render_quad);
}


uint32_t ltimer_get_ticks(LTimer *t) {
    uint32_t time = 0;
    if (t->started) {
        time = SDL_GetTicks() - t->start_ticks;
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


int main(int argc, char *argv[]) {
    check(initialize(), "Failed to initialize");
    check(load_media(), "Failed to load media");
    bool quit = false;
    SDL_Event e;

    /* the dot we will move around */
    Dot dot = {0, 0, 0, 0, NULL};
    SDL_Rect colliders[N_COLLIDERS] = {
        {0, 0,  6, 1},
        {0, 0, 10, 1},
        {0, 0, 14, 1},
        {0, 0, 16, 2},
        {0, 0, 18, 2},
        {0, 0, 20, 6},
        {0, 0, 18, 2},
        {0, 0, 16, 2},
        {0, 0, 14, 1},
        {0, 0, 10, 1},
        {0, 0,  6, 1}
    };
    dot.colliders = colliders;
    dot_shift_colliders(&dot);

    /* the dot we will collide against */
    Dot other_dot = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 0, 0, NULL};
    SDL_Rect other_colliders[N_COLLIDERS] = {
        {0, 0,  6, 1},
        {0, 0, 10, 1},
        {0, 0, 14, 1},
        {0, 0, 16, 2},
        {0, 0, 18, 2},
        {0, 0, 20, 6},
        {0, 0, 18, 2},
        {0, 0, 16, 2},
        {0, 0, 14, 1},
        {0, 0, 10, 1},
        {0, 0,  6, 1}
    };
    other_dot.colliders = other_colliders;
    dot_shift_colliders(&other_dot);

    LTimer cap_timer;

    while (!quit) {
        ltimer_start(&cap_timer);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            dot_handle_event(&dot, e);
        }
        dot_move(&dot, other_dot.colliders);
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        dot_render(&dot);
        dot_render(&other_dot);
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
