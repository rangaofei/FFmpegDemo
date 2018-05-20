//
// Created by saka on 18-5-20.
//

//
// Created by saka on 18-5-18.
//

#include <SDL2/SDL.h>
#include <stdio.h>
#include "res_path.h"

enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
SDL_Surface *hello = NULL;
SDL_Surface *keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface *currentSurface;

bool init();

bool loadMedia();

void close();

bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error:%s\n", SDL_GetError());
        success = false;
    } else {
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created!SDL_Error:%s\n", SDL_GetError());
            success = false;
        } else {
            surface = SDL_GetWindowSurface(window);
        }
    }
    return success;
}

SDL_Surface *loadSurface(std::string path) {
    SDL_Surface *optimizedSurface = nullptr;
    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load iamge %s! SDL Error:%s\n", path.c_str(), SDL_GetError());
    } else {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, surface->format, NULL);
        if (optimizedSurface == nullptr) {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

bool loadMedia() {
    bool success = true;
    std::string resPath = getResourcePath("l4") + "press.bmp";
    keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface(resPath);
    if (keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr) {
        printf("Failed to load default image\n");
        success = false;
    }

    resPath = getResourcePath("l4") + "up.bmp";
    keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface(resPath);
    if (keyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr) {
        printf("Failed to load up image!\n");
        success = false;
    }

    resPath = getResourcePath("l4") + "down.bmp";
    keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface(resPath);
    if (keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr) {
        printf("Failed to load down image!\n");
        success = false;
    }

    resPath = getResourcePath("l4") + "left.bmp";
    keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface(resPath);
    if (keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr) {
        printf("Failed to load left image!\n");
        success = false;
    }

    resPath = getResourcePath("l4") + "right.bmp";
    keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface(resPath);
    if (keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr) {
        printf("Failed to load right image!\n");
        success = false;
    }
    return success;
}

void close() {
    SDL_FreeSurface(hello);
    hello = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

int main(int argc, char *args[]) {

    if (!init()) {
        printf("Failed to initialize!\n");
        close();
        return -1;
    }
    if (!loadMedia()) {
        printf("Failed to laod media!\n");
    } else {
        bool quit = false;
        SDL_Event e;
        currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
        while (!quit) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP:
                            currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_UP];
                            break;
                        case SDLK_DOWN:
                            currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                            break;
                        case SDLK_LEFT:
                            currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                            break;
                        case SDLK_RIGHT:
                            currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                            break;
                        default:
                            currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                    }
                }
            }
            SDL_Rect stretchRect;
            stretchRect.x = 0;
            stretchRect.y = 0;
            stretchRect.w = SCREEN_HEIGHT;
            stretchRect.h = SCREEN_HEIGHT;
            SDL_BlitSurface(currentSurface, NULL, surface, &stretchRect);
            SDL_UpdateWindowSurface(window);
        }

    }
    close();

    return 0;
}