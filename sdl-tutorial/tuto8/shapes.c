#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


bool initialize();
bool load_media();
void close_all();
SDL_Texture *load_texture(char *);
SDL_Window *global_window = NULL;
SDL_Renderer *global_renderer = NULL;


bool initialize() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not initialize: %s\n", SDL_GetError());
        success = false;
    }
    else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            fprintf(stderr, "Linear texture filtering not enabled\n");
        }
        global_window = SDL_CreateWindow(
            "SDL Tuto 8",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0
        );
        if (global_window == NULL) {
            fprintf(stderr, "Could not create main window: %s\n", SDL_GetError());
            success = false;
        }
        else {
            global_renderer = SDL_CreateRenderer(global_window, -1, SDL_RENDERER_ACCELERATED);
            if (global_renderer == NULL) {
                fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(global_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
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
    return success;
}


void close_all() {
    SDL_DestroyRenderer(global_renderer);
    global_renderer = NULL;
    SDL_DestroyWindow(global_window);
    global_window = NULL;
    IMG_Quit();
    SDL_Quit();
}


SDL_Texture *load_texture(char *path) {
    SDL_Texture *final_texture = NULL;
    SDL_Surface *loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL) {
        fprintf(stderr, "Could not load image '%s': %s\n", path, IMG_GetError());
    }
    else {
        final_texture = SDL_CreateTextureFromSurface(global_renderer, loaded_surface);
        if (final_texture == NULL) {
            fprintf(stderr, "Could not create texture from '%s': %s\n", path, SDL_GetError());
        }
        SDL_FreeSurface(loaded_surface);
    }
    return final_texture;
}


int main(int argc, char *argv[]) {
    if (initialize()) {
        if (load_media()) {
            bool quit = false;
            SDL_Event e;
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                /* clear screen */
                SDL_SetRenderDrawColor(global_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(global_renderer);

                /* draw red-filled rectangle */
                SDL_Rect fill_rect = {SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
                SDL_SetRenderDrawColor(global_renderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(global_renderer, &fill_rect);

                /* draw green hollow rectangle */
                SDL_Rect hollow_rect = {SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH*2/3, SCREEN_HEIGHT*2/3};
                SDL_SetRenderDrawColor(global_renderer, 0x00, 0xFF, 0x00, 0xFF);
                SDL_RenderDrawRect(global_renderer, &hollow_rect);

                /* draw blue horizontal line */
                SDL_SetRenderDrawColor(global_renderer, 0x00, 0x00, 0xFF, 0xFF);
                SDL_RenderDrawLine(global_renderer, 0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);

                /* draw vertical orange dotted line */
                SDL_SetRenderDrawColor(global_renderer, 0xFF, 0x77, 0x00, 0xFF);
                for (int i = 0; i < SCREEN_HEIGHT; i++) {
                    SDL_RenderDrawPoint(global_renderer, SCREEN_WIDTH/2, i);
                }

                SDL_RenderPresent(global_renderer);
            }
        }
    }
    close_all();
    return 0;
}
