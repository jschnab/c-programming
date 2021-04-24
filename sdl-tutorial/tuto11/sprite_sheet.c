#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


typedef struct ltexture {
    SDL_Texture *texture;
    int width;
    int height;
} LTexture;


bool initialize();
bool load_media(LTexture *, char*);
void close_all();
LTexture *ltexture_init();
bool ltexture_from_file(LTexture *, char *);
void ltexture_destroy(LTexture *);
void ltexture_render(LTexture *, int, int, SDL_Rect *);


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Rect sprite_clips[4];


LTexture *ltexture_init() {
    LTexture *t = malloc(sizeof(LTexture));
    if (t == NULL) {
        fprintf(stderr, "Could not create LTexture\n");
        return NULL;
    }
    t->texture = NULL;
    t->width = 0;
    t->height = 0;
    return t;
}


void ltexture_destroy(LTexture *t) {
    if (t->texture != NULL) {
        SDL_DestroyTexture(t->texture);
        free(t);
    }
}


bool ltexture_from_file(LTexture *t, char *path) {
    free(t->texture);
    SDL_Texture *final_texture = NULL;
    SDL_Surface *loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        fprintf(stderr, "Could not load image '%s': %s\n", path, IMG_GetError());
    }
    else {
        SDL_SetColorKey(
            loaded_surface,
            SDL_TRUE,
            SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF)
        );

        final_texture = SDL_CreateTextureFromSurface(gRenderer, loaded_surface);
        if (final_texture == NULL) {
            fprintf(stderr, "Could not create texture from '%s': %s\n", path, SDL_GetError());
        }
        else {
            t->width = loaded_surface->w;
            t->height = loaded_surface->h;
        }
        SDL_FreeSurface(loaded_surface);
    }
    t->texture = final_texture;
    return t->texture != NULL;
}


void ltexture_render(LTexture *t, int x, int y, SDL_Rect *clip) {
    SDL_Rect render_quad = {x, y, t->width, t->height};
    if (clip != NULL) {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, t->texture, clip, &render_quad);
}


bool initialize() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        success = false;
    }
    else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            fprintf(stderr, "Linear texture filtering not enabled\n");
        }
        gWindow = SDL_CreateWindow(
            "SDL Tuto 11",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0
        );
        if (gWindow == NULL) {
            fprintf(stderr, "Could not create main window: %s\n", SDL_GetError());
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int img_flags = IMG_INIT_PNG;
                if (!(IMG_Init(img_flags) & img_flags)) {
                    fprintf(stderr, "Could not initialize SDL_image: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}


bool load_media(LTexture *t, char *path) {
    bool success = true;
    if (!ltexture_from_file(t, path)) {
        fprintf(stderr, "Could not load sprite sheet '%s'\n", path);
        success = false;
    }
    else {
        /* top left sprite */
        sprite_clips[0].x = 0;
        sprite_clips[0].y = 0;
        sprite_clips[0].w = 100;
        sprite_clips[0].h = 100;

        /* top right sprite */
        sprite_clips[1].x = 100;
        sprite_clips[1].y = 0;
        sprite_clips[1].w = 100;
        sprite_clips[1].h = 100;

        /* bottom left sprite */
        sprite_clips[2].x = 0;
        sprite_clips[2].y = 100;
        sprite_clips[2].w = 100;
        sprite_clips[2].h = 100;

        /* bottom right sprite */
        sprite_clips[3].x = 100;
        sprite_clips[3].y = 100;
        sprite_clips[3].w = 100;
        sprite_clips[3].h = 100;
    }
    return success;
}


void close_all() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char *argv[]) {
    if (initialize()) {
        LTexture *sprite_sheet = ltexture_init();
        if (load_media(sprite_sheet, "sprites.png")) {
            bool quit = false;
            SDL_Event e;
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                /* render top left sprite */
                ltexture_render(
                    sprite_sheet,
                    0,
                    0,
                    &sprite_clips[0]
                );

                /* render top right sprite */
                ltexture_render(
                    sprite_sheet,
                    SCREEN_WIDTH - sprite_clips[1].w,
                    0,
                    &sprite_clips[1]
                );

                /* render bottom left sprite */
                ltexture_render(
                    sprite_sheet,
                    0,
                    SCREEN_HEIGHT - sprite_clips[2].h,
                    &sprite_clips[2]
                );

                /* render bottom right sprite */
                ltexture_render(
                    sprite_sheet,
                    SCREEN_WIDTH - sprite_clips[3].w,
                    SCREEN_HEIGHT - sprite_clips[3].h,
                    &sprite_clips[3]
                );

                SDL_RenderPresent(gRenderer);
            }
            ltexture_destroy(sprite_sheet);
        }
    }
    
    close_all();
    return 0;
}
