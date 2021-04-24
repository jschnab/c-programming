# SDL2 library cheet sheet

## Functions

### SDL_Init

Initialize the SDL library.

```
int SDL_Init(Uint32 flags);
```

Parameters:
* `flags`: subsystem initialization flags.

Usual flags include (amont others):
* `SDL_INIT_TIMER`: timer subsystem
* `SDL_INIT_AUDIO`: audio subsystem
* `SDL_INIT_VIDEO`: video subsystem (automatically initializes events
  subsystem)
* `SDL_INIT_JOYSTICK`: joystick subsystem
* `SDL_INIT_EVERYTHING`: all subsystems

Returns 0 on success or a negative error code on failure. Calling
`SDL_GetError()` provides more information on failure.

### SDL_Quit

Clean up all initialized SDL subsystems.

```
void SDL_Quit(void);
```

It is safe to call this function when there are initialization errors.

### IMG_Init

Initialize the `SDL_image` subsystems.

```
int IMG_Init(int flags);
```

Parameters:
* `flags`: indicateimage loading support, can be OR'd together

Flags include:
* `IMG_INIT_JPG`
* `IMG_INIT_PNG`
* `IMG_INIT_TIF`

Returns a bitmask of all the currently initiated image loaders. To get more
information about a failure, call `IMG_GetError()`.

This function is idempotent.

### IMG_Quit

Cleans up all dynamically loaded library handles, freeing memory.

```
void IMG_Quit(void);
```

### SDL_CreateWindow

Create an `SDL_Window` struct.

```
SDL_Window \* SDL_CreateWindow(
    const char * title,
    int x,
    int y,
    int w,
    int h,
    Uint32 flags
);
```

Parameters:
* `title`: title of the window in UTF-8 encoding
* `x`: x position of the window, `SDL_WINDOWPOS_CENTERED` or `SDL_WINDOWPOS_UNDEFINED`
* `y`: y position of the window, `SDL_WINDOWPOS_CENTERED` or `SDL_WINDOWPOS_UNDEFINED`
* `w`: width of the window
* `h`: height of the window
* `flags`: 0, or one or more [SDL_WindowFlags](https://wiki.libsdl.org/SDL_WindowFlags) OR'd together

Returns the window that was created or NULL on failure.

### SDL_CreateRenderer

Create a 2D rendering context for a window.

```
SDL_Renderer \* SDL_CreateRenderer(
    SDL_Window * window,
    int index,
    Uint32 flags
);
```

Parameters:
* `window`: window where rendering is displayed
* `index`: index of the rendering driver, or -1 to initialize the first driver
  supporting the requested flags
* `flags`: 0, or one or more [SDL_RendererFlags](https://wiki.libsdl.org/SDL_RendererFlags) OR'd together

Returns a rendering context or NULL if there was an error.

Renderer flags include (among others):
* `SDL_RENDERER_SOFTWARE`: fallback
* `SDL_RENDERER_ACCELERATED`: uses hardware acceleration

### SDL_SetRenderDrawColor

Set the color used for drawing operations (Rect, Line, and Clear).

```
int SDL_SetRenderDrawColor(
    SDL_Renderer * renderer,
    Uint8 r,
    Uint8 g,
    Uint8 b,
    Uint8 a
);
```

Parameters:
* `renderer` rendering context
* `r`: red value
* `g`: green value
* `b`: blue value
* `a`: alpha value, usually `SDL_ALPHA_OPAQUE` (255)

Returns 0 or success or a negative error code on failure.

