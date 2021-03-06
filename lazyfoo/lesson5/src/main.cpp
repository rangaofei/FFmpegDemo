//
// Created by saka on 18-5-20.
//

//
// Created by saka on 18-5-18.
//

#include <SDL2/SDL.h>
#include <stdio.h>
#include "res_path.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
SDL_Surface *stretchSurface = NULL;


bool init();

bool loadMedia();

void close();

SDL_Surface *loadSurface(std::string path);

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

SDL_Surface *loadSurface(const std::string path) {
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
    std::string resPath = getResourcePath("l5") + "stretch.bmp";
    stretchSurface = loadSurface(resPath);
    if (stretchSurface == NULL) {
        printf("Failed to load stretching image!\n");
        success = false;
    }
    return success;
}

void close() {
    SDL_FreeSurface(stretchSurface);
    stretchSurface = NULL;
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
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
            SDL_Rect stretchRect;
            stretchRect.x = 0;
            stretchRect.y = 0;
            stretchRect.w = SCREEN_WIDTH;
            stretchRect.h = SCREEN_HEIGHT;
            SDL_BlitScaled(stretchSurface, NULL, surface, NULL);
            SDL_UpdateWindowSurface(window);
        }

    }

    close();

    return 0;
}