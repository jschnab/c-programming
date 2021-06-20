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
const int DOT_VEL = 4;


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
    Circle collider;
} Dot;


typedef struct ltimer {
    uint32_t start_ticks;
    bool started;
} LTimer;


bool check_collision_circle_box(Circle, SDL_Rect);
bool check_collision_circle_circle(Circle, Circle);
void close_all();
double distance_squared(int, int, int, int);
void dot_handle_event(Dot *, SDL_Event);
void dot_move(Dot *, SDL_Rect, Circle);
void dot_render(Dot *);
void dot_shift_colliders(Dot *);
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


bool check_collision_circle_box(Circle circle, SDL_Rect box) {
    /* closest point on collision box */
    int cx, cy;

    /* find closest x offset */
    if (circle.x < box.x) {
        cx = box.x;
    }
    else if (circle.x > box.x + box.w) {
        cx = box.x + box.w;
    }
    else {
        cx = circle.x;
    }

    /* find closest y offset */
    if (circle.y < box.y) {
        cy = box.y;
    }
    else if (circle.y > box.y + box.h) {
        cy = box.y + box.h;
    }
    else {
        cy = circle.y;
    }

    /* if the closest point is inside the circle, there's a collision */
    if (distance_squared(circle.x, circle.y, cx, cy) < circle.r * circle.r) {
        return true;
    }

    return false;
}


bool check_collision_circle_circle(Circle a, Circle b) {
    int total_radius_squared = (a.r + b.r) * (a.r + b.r);

    /* if the distance between the centers of the circles is less than
     * the sum of their radii, there's a collision */
    if (distance_squared(a.x, a.y, b.x, b.y) < total_radius_squared) {
        return true;
    }

    return false;
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


void dot_move(Dot *dot, SDL_Rect square, Circle circle) {
    /* move the dot left or right */
    dot->posx += dot->velx;
    dot_shift_colliders(dot);

    /* if the dot collided or went too far left or right */
    if (
        dot->posx - dot->collider.r < 0 ||
        dot->posx + dot->collider.r > SCREEN_WIDTH ||
        check_collision_circle_box(dot->collider, square) ||
        check_collision_circle_circle(dot->collider, circle)
    ) {
        /* move back */
        dot->posx -= dot->velx;
        dot_shift_colliders(dot);
    }

    /* move the dot up or down */
    dot->posy += dot->vely;
    dot_shift_colliders(dot);

    /* if the dot collided or went too far up or down */
    if (
        dot->posy - dot->collider.r < 0 ||
        dot->posy + dot->collider.r > SCREEN_HEIGHT ||
        check_collision_circle_box(dot->collider, square) ||
        check_collision_circle_circle(dot->collider, circle)
    ) {
        /* move back */
        dot->posy -= dot->vely;
        dot_shift_colliders(dot);
    }
}


void dot_render(Dot *dot) {
    ltexture_render(
        &gDotTexture,
        dot->posx - dot->collider.r,
        dot->posy - dot->collider.r,
        NULL
    );
}


void dot_shift_colliders(Dot *dot) {
    dot->collider.x = dot->posx;
    dot->collider.y = dot->posy;
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
        {
            DOT_WIDTH / 2,
            DOT_HEIGHT / 2,
            DOT_WIDTH / 2
        }
    };
    Dot other_dot = {
        SCREEN_WIDTH / 4,
        SCREEN_HEIGHT / 4,
        0,
        0,
        {
            SCREEN_WIDTH / 4,
            SCREEN_HEIGHT / 4,
            DOT_WIDTH / 2
        }
    };
    SDL_Rect wall;
    wall.x = 300;
    wall.y = 40;
    wall.w = 40;
    wall.h = 400;

    LTimer cap_timer;

    while (!quit) {
        ltimer_start(&cap_timer);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            dot_handle_event(&dot, e);
        }
        dot_move(&dot, wall, other_dot.collider);
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawRect(gRenderer, &wall);
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
