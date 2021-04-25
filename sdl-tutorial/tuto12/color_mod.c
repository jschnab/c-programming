#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>


typedef struct ltexture {
    SDL_Texture *texture;
    int width;
    int height;
} LTexture;


bool initialize();
bool load_media();
void close_all();
void ltexture_destroy(LTexture *);
bool ltexture_from_file(LTexture *, char *);
void ltexture_render(LTexture *, int, int, SDL_Rect *);
void ltexture_set_color(LTexture *, uint8_t, uint8_t, uint8_t);


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
LTexture gTexture = {NULL, 0, 0};


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
    SDL_Texture *final_texture = NULL;
    SDL_Surface *loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        fprintf(stderr, "Could not load '%s': %s\n", path, IMG_GetError());
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


void ltexture_set_color(LTexture *t, uint8_t red, uint8_t green, uint8_t blue) {
    SDL_SetTextureColorMod(t->texture, red, green, blue);
}


bool initialize() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL could not initialize: %s\n", SDL_GetError());
        success = false;
    }
    else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            fprintf(stderr, "Linear texture filtering not enabled\n");
        }
        gWindow = SDL_CreateWindow(
            "SDL Tuto 12",
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
                fprintf(stderr, "Could not create main renderer: %s\n", SDL_GetError());
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int img_flags = IMG_INIT_PNG;
                if (!(IMG_Init(img_flags) & img_flags)) {
                    fprintf(stderr, "SDL_image could not initialize: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}


bool load_media() {
    bool success = true;
    if (!ltexture_from_file(&gTexture, "colors.png")) {
        fprintf(stderr, "Failed to load colors texture\n");
        success = false;
    }
    return success;
}


void close_all() {
    ltexture_destroy(&gTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char *argv[]) {
    if (initialize()) {
        if (load_media()) {
            bool quit = false;
            SDL_Event e;
            uint8_t r = 255;
            uint8_t g = 255;
            uint8_t b = 255;
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    else if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                            case SDLK_q:
                                r += 32;
                                break;
                            case SDLK_w:
                                g += 32;
                                break;
                            case SDLK_e:
                                b += 32;
                                break;
                            case SDLK_a:
                                r -= 32;
                                break;
                            case SDLK_s:
                                g -= 32;
                                break;
                            case SDLK_d:
                                b -= 32;
                                break;
                        }
                    }
                }
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                ltexture_set_color(&gTexture, r, g, b);
                ltexture_render(&gTexture, 0, 0, NULL);
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    close_all();
    return 0;
}
