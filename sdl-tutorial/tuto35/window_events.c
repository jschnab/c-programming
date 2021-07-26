#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../debug.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


typedef struct ltexture {
    SDL_Texture *texture;
    int width;
    int height;
} LTexture;


typedef struct lwindow {
    SDL_Window *window;
    int width;
    int height;
    bool mouse_focus;
    bool keyboard_focus;
    bool full_screen;
    bool minimized;
} LWindow;


void close_all();
bool initialize();
bool load_media();
void ltexture_destroy(LTexture *);
bool ltexture_from_file(LTexture *, char *);
void ltexture_render(LTexture *, int, int, SDL_Rect *);
SDL_Renderer *lwindow_create_renderer(LWindow *);
void lwindow_destroy(LWindow *);
void lwindow_handle_event(LWindow *, SDL_Event);
bool lwindow_init(LWindow *);


LWindow gWindow = {NULL, 0, 0, false, false, false, false};
SDL_Renderer *gRenderer = NULL;
LTexture gSceneTexture = {NULL, 0, 0};
char string_buffer[100];


void close_all() {
    ltexture_destroy(&gSceneTexture);
    SDL_DestroyRenderer(gRenderer);
    lwindow_destroy(&gWindow);
    IMG_Quit();
    SDL_Quit();
}


bool initialize() {
    check(
        SDL_Init(SDL_INIT_VIDEO) == 0,
        "SDL failed to initialize: %s",
        SDL_GetError()
    );
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        fprintf(stderr, "Warning: linear texture filtering not enabled\n");
    }
    check(lwindow_init(&gWindow), "Window could not be created: %s", SDL_GetError());
    gRenderer = lwindow_create_renderer(&gWindow);
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
    check(
        ltexture_from_file(&gSceneTexture, "window.png"),
        "Failed to load window texture"
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


SDL_Renderer *lwindow_create_renderer(LWindow *w) {
    return SDL_CreateRenderer(
        w->window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
}


void lwindow_destroy(LWindow *w) {
    if (w->window != NULL) {
        SDL_DestroyWindow(w->window);
    }
    w->mouse_focus = false;
    w->keyboard_focus = false;
    w->width = 0;
    w->height = 0;
}


void lwindow_handle_event(LWindow *w, SDL_Event e) {
    if (e.type == SDL_WINDOWEVENT) {
        bool update_caption = false;

        switch (e.window.event) {
            /* get new dimensions and repaint on window size change */
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                w->width = e.window.data1;
                w->height = e.window.data2;
                SDL_RenderPresent(gRenderer);
                break;

            /* repaint on exposure */
            case SDL_WINDOWEVENT_EXPOSED:
                SDL_RenderPresent(gRenderer);
                break;

            /* mouse entered window */
            case SDL_WINDOWEVENT_ENTER:
                w->mouse_focus = true;
                update_caption = true;
                break;

            /* mouse left window */
            case SDL_WINDOWEVENT_LEAVE:
                w->mouse_focus = false;
                update_caption = true;
                break;

            /* window has keyboard focus */
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                w->keyboard_focus = true;
                update_caption = true;
                break;

            /* case SDL_WINDOWEVENT_FOCUS_LOST */
            case SDL_WINDOWEVENT_FOCUS_LOST:
                w->keyboard_focus = false;
                update_caption = true;
                break;

            /* window minimized */
            case SDL_WINDOWEVENT_MINIMIZED:
                w->minimized = true;
                break;

            /* window maximized */
            case SDL_WINDOWEVENT_MAXIMIZED:
                w->minimized = false;
                break;

            /* window restored */
            case SDL_WINDOWEVENT_RESTORED:
                w->minimized = false;
                break;
        }

        /* update window caption with new data */
        if (update_caption) {
            sprintf(
                string_buffer,
                "Mouse Focus: %s - Keyboard Focus: %s",
                w->mouse_focus ? "On" : "Off",
                w->keyboard_focus ? "On" : "Off"
            );
            SDL_SetWindowTitle(w->window, string_buffer);
        }
    }

    /* enter/exit full screen on return key */
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
        if (w->full_screen) {
            SDL_SetWindowFullscreen(w->window, SDL_FALSE);
            w->full_screen = false;
        }
        else {
            SDL_SetWindowFullscreen(w->window, SDL_TRUE);
            w->full_screen = true;
            w->minimized = false;
        }
    }
}


bool lwindow_init(LWindow *w) {
    w->window = SDL_CreateWindow(
        "SDL Tuto 35",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    check_mem(w->window);
    w->mouse_focus = true;
    w->keyboard_focus = true;
    w->width = SCREEN_WIDTH;
    w->height = SCREEN_HEIGHT;
    return true;

    error:
        return false;
}


int main(int argc, char *argv[]) {
    check(initialize(), "Failed to initialize");
    check(load_media(), "Failed to initialize");
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            lwindow_handle_event(&gWindow, e);
        }

        /* only draw when not minimized */
        if (!gWindow.minimized) {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            ltexture_render(
                &gSceneTexture,
                (gWindow.width - gSceneTexture.width) / 2,
                (gWindow.height - gSceneTexture.height) / 2,
                NULL
            );
            SDL_RenderPresent(gRenderer);
        }
    }
    close_all();
    return 0;

    error:
        close_all();
        return -1;
}
