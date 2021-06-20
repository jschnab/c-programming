#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../debug.h"


#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME (1000 / SCREEN_FPS)


const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int DOT_WIDTH = 20;
const int DOT_HEIGHT = 20;
const int DOT_VEL = 10;


typedef struct circle {
    int x, y, r;
} Circle;


typedef struct ltexture {
    SDL_Texture *texture;
    int width;
    int height;
} LTexture;


typedef struct dot {
    int posx, posy;
    int velx, vely;
} Dot;


typedef struct ltimer {
    uint32_t start_ticks;
    bool started;
} LTimer;


void close_all();
void dot_handle_event(Dot *, SDL_Event);
void dot_move(Dot *);
void dot_render(Dot *, int, int);
bool initialize();
bool load_media();
void ltexture_destroy(LTexture *);
bool ltexture_from_file(LTexture *, char *);
void ltexture_render(LTexture *, int, int, SDL_Rect *);
uint32_t ltimer_get_ticks(LTimer *);
void ltimer_start(LTimer *);
void ltimer_stop(LTimer *);


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
LTexture gDotTexture = {NULL, 0, 0};
LTexture gBackgroundTexture = {NULL, 0, 0};


void close_all() {
    ltexture_destroy(&gDotTexture);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}


double distance_squared(int x1, int y1, int x2, int y2) {
    int delta_x = x2 - x1;
    int delta_y = y2 - y1;
    return delta_x * delta_x + delta_y * delta_y;
}


void dot_handle_event(Dot *dot, SDL_Event e) {
    /* if a key was pressed */
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
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


void dot_move(Dot *dot) {
    /* move the dot left or right */
    dot->posx += dot->velx;

    /* if the dot collided or went too far left or right */
    if (dot->posx < 0 || dot->posx + DOT_WIDTH > LEVEL_WIDTH) {
        /* move back */
        dot->posx -= dot->velx;
    }

    /* move the dot up or down */
    dot->posy += dot->vely;

    /* if the dot collided or went too far up or down */
    if (dot->posy < 0 || dot->posy + DOT_HEIGHT > LEVEL_HEIGHT) {
        /* move back */
        dot->posy -= dot->vely;
    }
}


void dot_render(Dot *dot, int camx, int camy) {
    ltexture_render(
        &gDotTexture,
        dot->posx - camx,
        dot->posy - camy,
        NULL
    );
}


bool initialize() {
    check(
        SDL_Init(SDL_INIT_VIDEO) == 0,
        "SDL failed to initialize: %s",
        SDL_GetError()
    );
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        log_warn("Linear texture filtering not enabled.");
    }
    gWindow = SDL_CreateWindow(
        "SDL Tuto 29",
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
    check(
        ltexture_from_file(&gBackgroundTexture, "bg.png"),
        "Failed to load background texture"
    );
    return true;

    error:
        return false;
}


void ltexture_destroy(LTexture *t) {
    if (t->texture != NULL) {
        SDL_DestroyTexture(t->texture);
        t->texture = NULL;
    }
    t->width = 0;
    t->height = 0;
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
    t->start_ticks = SDL_GetTicks();
}


void ltimer_stop(LTimer *t) {
    t->started = false;
    t->start_ticks = 0;
}


int main(int argc, char *argv[]) {
    check(initialize(), "Failed to initialize");
    check(load_media(), "Failed to load media");
    bool quit = false;
    SDL_Event e;
    Dot dot = {
        DOT_WIDTH / 2,
        DOT_HEIGHT / 2,
        0,
        0,
    };
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    LTimer cap_timer;

    while (!quit) {
        ltimer_start(&cap_timer);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            dot_handle_event(&dot, e);
        }
        dot_move(&dot);

        /* center the camera over the dot */
        camera.x = dot.posx + DOT_WIDTH / 2 - SCREEN_WIDTH / 2;
        camera.y = dot.posy + DOT_HEIGHT / 2 - SCREEN_HEIGHT / 2;

        /* keep the camera in bounds */
        if (camera.x < 0) {
            camera.x = 0;
        }
        if (camera.y < 0) {
            camera.y = 0;
        }
        if (camera.x > LEVEL_WIDTH - camera.w) {
            camera.x = LEVEL_WIDTH - camera.w;
        }
        if (camera.y > LEVEL_HEIGHT - camera.h) {
            camera.y = LEVEL_HEIGHT - camera.h;
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        ltexture_render(&gBackgroundTexture, 0, 0, &camera);
        dot_render(&dot, camera.x, camera.y);
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
