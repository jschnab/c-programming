#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <stdio.h>

#include "../debug.h"


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
bool ltexture_from_file(LTexture *, char *);
void ltexture_render(LTexture *, int, int, SDL_Rect *);


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
LTexture gPromptTexture;
Mix_Music *gMusic = NULL;
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;


void close_all() {
    ltexture_destroy(&gPromptTexture);
    Mix_FreeChunk(gScratch);
    gScratch = NULL;
    Mix_FreeChunk(gHigh);
    gHigh = NULL;
    Mix_FreeChunk(gMedium);
    gMedium = NULL;
    Mix_FreeChunk(gLow);
    gLow = NULL;
    Mix_FreeMusic(gMusic);
    gMusic = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}


bool initialize() {
    check(
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0,
        "SDL could not initialize: %s\n",
        SDL_GetError()
    );
    check(
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"),
        "Linear texture filtering not enabled"
    );
    gWindow = SDL_CreateWindow(
        "SDL Tuto 21",
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
        "SDL_image could not initialize: %s",
        IMG_GetError()
    );
    check(
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0,
        "SDL_mixer could not initialize: %s",
        Mix_GetError()
    );
    return true;

    error:
        return false;
}


bool load_media() {
    check(
        ltexture_from_file(&gPromptTexture, "prompt.png"),
        "Failed to load prompt texture"
    );
    gMusic = Mix_LoadMUS("beat.wav");
    check_mem(gMusic);
    gScratch = Mix_LoadWAV("scratch.wav");
    check_mem(gScratch);
    gHigh = Mix_LoadWAV("high.wav");
    check_mem(gHigh);
    gMedium = Mix_LoadWAV("medium.wav");
    check_mem(gMedium);
    gLow = Mix_LoadWAV("low.wav");
    check_mem(gLow);
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
    t->width = loaded_surface->w;
    t->height = loaded_surface->h;
    SDL_FreeSurface(loaded_surface);
    check_mem(t->texture);
    return true;

    error:
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


int main(int argc, char *argv[]) {
    check(initialize(), "Failed to initialize");
    check(load_media(), "Failed to load media");
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_1:
                        Mix_PlayChannel(-1, gHigh, 0);
                        break;
                    case SDLK_2:
                        Mix_PlayChannel(-1, gMedium, 0);
                        break;
                    case SDLK_3:
                        Mix_PlayChannel(-1, gLow, 0);
                        break;
                    case SDLK_4:
                        Mix_PlayChannel(-1, gScratch, 0);
                        break;
                    case SDLK_9:
                        if (Mix_PlayingMusic() == 0) {  /* no music is playing */
                            Mix_PlayMusic(gMusic, -1);
                        }
                        else {  /* music is being played */
                            if (Mix_PausedMusic() == 1) {  /* music is paused */
                                Mix_ResumeMusic();
                            }
                            else {  /* music is playing */
                                Mix_PauseMusic();
                            }
                        }
                        break;
                    case SDLK_0:
                        Mix_HaltMusic();
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        ltexture_render(&gPromptTexture, 0, 0, NULL);
        SDL_RenderPresent(gRenderer);
    }
    close_all();
    return 0;

    error:
        return -1;
}
