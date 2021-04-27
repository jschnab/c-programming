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
LTexture gTextureFront = {NULL, 0, 0};
LTexture gTextureBack = {NULL, 0, 0};

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


void ltexture_set_color(LTexture *t, uint8_t red, uint8_t green, uint8_t blue) {
    SDL_SetTextureColorMod(t->texture, red, green, blue);
}


void ltexture_set_blend_mode(LTexture *t, SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(t->texture, blending);
}


void ltexture_set_alpha(LTexture *t, uint8_t alpha) {
    SDL_SetTextureAlphaMod(t->texture, alpha);
}


bool initialize() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL could not initialize: %s\n", SDL_GetError());
        success = false;
    }
    else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            fprintf(stderr, "Linear texture filtering is not enabled\n");
        }
        gWindow = SDL_CreateWindow(
            "SDL Tuto 13",
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
    if (!ltexture_from_file(&gTextureFront, "fadeout.png")) {
        fprintf(stderr, "Could not load front texture\n");
        success = false;
    }
    else {
        ltexture_set_blend_mode(&gTextureBack, SDL_BLENDMODE_BLEND);
    }
    if (!ltexture_from_file(&gTextureBack, "fadein.png")) {
        fprintf(stderr, "Could not load background texture \n");
        success = false;
    }
    return success;
}


void close_all() {
    ltexture_destroy(&gTextureFront);
    ltexture_destroy(&gTextureBack);
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
            uint8_t alpha = 255;
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    else if (e.type == SDL_KEYDOWN) {
                        if (e.key.keysym.sym == SDLK_w) {
                            if (alpha + 32 > 255) {
                                alpha = 255;
                            }
                            else {
                                alpha += 32;
                            }
                        }
                        else if (e.key.keysym.sym == SDLK_s) {
                            if (alpha - 32 < 0) {
                                alpha = 0;
                            }
                            else {
                                alpha -= 32;
                            }
                        }
                    }
                }
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                ltexture_render(&gTextureBack, 0, 0, NULL);
                ltexture_set_alpha(&gTextureFront, alpha);
                ltexture_render(&gTextureFront, 0, 0, NULL);
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    close_all();
    return 0;
}
