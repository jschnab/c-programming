#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../debug.h"

/* number of data integers */
#define TOTAL_DATA 10


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


typedef struct ltexture {
    SDL_Texture *texture;
    int width;
    int height;
} LTexture;


void close_all();
bool initialize();
bool load_media();
void ltexture_destroy(LTexture *);
bool ltexture_from_text(LTexture *, char *, SDL_Color);
void ltexture_render(LTexture *, int, int, SDL_Rect *);


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;

LTexture gPromptTexture = {NULL, 0, 0};
LTexture gDataTextures[TOTAL_DATA];
int32_t gData[TOTAL_DATA];
char string_buffer[10];


void close_all() {
    /* save data */
    SDL_RWops * file = SDL_RWFromFile("nums.bin", "w+b");
    if (file != NULL) {
        for (int i = 0; i < TOTAL_DATA; i++) {
            SDL_RWwrite(file, &gData[i], sizeof(int32_t), 1);
        }
        SDL_RWclose(file);
    }
    else {
        printf("Error: failed to save data file\n");
    }

    /* free loaded images */
    ltexture_destroy(&gPromptTexture);
    for (int i = 0; i < TOTAL_DATA; i++) {
        ltexture_destroy(&gDataTextures[i]);
    }

    TTF_CloseFont(gFont);
    gFont = NULL;
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
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
        "Linear texture filtering is not enabled"
    );
    gWindow = SDL_CreateWindow(
        "SDL Tuto 32",
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
    check_mem(gFont);
    SDL_Color text_color = {0, 0, 0, 0xFF};
    SDL_Color highlight_color = {0xFF, 0, 0, 0xFF};
    check(
        ltexture_from_text(&gPromptTexture, "Enter text:", text_color),
        "Failed to render prompt text"
    );
    /* open a file for reading in binary */
    SDL_RWops *file = SDL_RWFromFile("nums.bin", "r+b");
    /* if file does not exist */
    if (file == NULL) {
        printf("Writing file nums.bin\n");
        file = SDL_RWFromFile("nums.bin", "w+b");
        check_mem(file);
        printf("New file created\n");
        for (int i = 0; i < TOTAL_DATA; i++) {
            gData[i] = 0;
            SDL_RWwrite(file, &gData[i], sizeof(int32_t), 1);
        }
        printf("Wrote data to file\n");
        SDL_RWclose(file);
        printf("Closed file\n");
    }
    /* file exists */
    else {
        printf("Reading file nums.bin\n");
        for (int i = 0; i < TOTAL_DATA; i++) {
            SDL_RWread(file, &gData[i], sizeof(int32_t), 1);
        }
        SDL_RWclose(file);
    }
    /* initialize data textures */
    sprintf(string_buffer, "%d", gData[0]),
    ltexture_from_text(
        &gDataTextures[0],
        string_buffer,
        highlight_color
    );
    for (int i = 1; i < TOTAL_DATA; i++) {
        sprintf(string_buffer, "%d", gData[i]),
        ltexture_from_text(
            &gDataTextures[i],
            string_buffer,
            text_color
        );
    }
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


bool ltexture_from_text(LTexture *t, char *text, SDL_Color color) {
    ltexture_destroy(t);
    SDL_Surface *text_surface = TTF_RenderText_Solid(gFont, text, color);
    check_mem(text_surface);
    t->texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);
    check_mem(t->texture);
    t->width = text_surface->w;
    t->height = text_surface->h;
    SDL_FreeSurface(text_surface);
    return true;

    error:
        SDL_FreeSurface(text_surface);
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


int main(int argc, char *argv[]) {
    check(initialize(), "Failed to initialize");
    check(load_media(), "Failed to load media");

    bool quit = false;
    SDL_Event e;
    SDL_Color text_color = {0, 0, 0, 0xFF};
    SDL_Color highlight_color = {0xFF, 0, 0, 0xFF};
    int current_data = 0;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    /* previous data entry */
                    case SDLK_UP:
                        /* re-render previous entry input point */
                        sprintf(string_buffer, "%d", gData[current_data]),
                        ltexture_from_text(
                            &gDataTextures[current_data],
                            string_buffer,
                            text_color
                        );
                        current_data--;
                        if (current_data < 0) {
                            current_data = TOTAL_DATA - 1;
                        }
                        /* re-render current entry point */
                        sprintf(string_buffer, "%d", gData[current_data]),
                        ltexture_from_text(
                            &gDataTextures[current_data],
                            string_buffer,
                            highlight_color
                        );
                        break;

                    /* next data entry */
                    case SDLK_DOWN:
                        /* re-rener previous entry input point */
                        sprintf(string_buffer, "%d", gData[current_data]),
                        ltexture_from_text(
                            &gDataTextures[current_data],
                            string_buffer,
                            text_color
                        );
                        current_data++;
                        if (current_data == TOTAL_DATA) {
                            current_data = 0;
                        }
                        /* re-render current entry input point */
                        sprintf(string_buffer, "%d", gData[current_data]),
                        ltexture_from_text(
                            &gDataTextures[current_data],
                            string_buffer,
                            highlight_color
                        );
                        break;

                    /* decrement input point */
                    case SDLK_LEFT:
                        gData[current_data]--;
                        sprintf(string_buffer, "%d", gData[current_data]),
                        ltexture_from_text(
                            &gDataTextures[current_data],
                            string_buffer,
                            highlight_color
                        );
                        break;

                    /* increment input point */
                    case SDLK_RIGHT:
                        gData[current_data]++;
                        sprintf(string_buffer, "%d", gData[current_data]),
                        ltexture_from_text(
                            &gDataTextures[current_data],
                            string_buffer,
                            highlight_color
                        );
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        ltexture_render(
            &gPromptTexture,
            (SCREEN_WIDTH - gPromptTexture.width) / 2,
            0,
            NULL
        );
        for (int i = 0; i < TOTAL_DATA; i++) {
            ltexture_render(
                &gDataTextures[i],
                (SCREEN_WIDTH - gDataTextures[i].width) / 2,
                gPromptTexture.height + gDataTextures[0].height * i,
                NULL
            );
        }
        SDL_RenderPresent(gRenderer);
    }

    close_all();
    return 0;

    error:
        close_all();
        return -1;
}
