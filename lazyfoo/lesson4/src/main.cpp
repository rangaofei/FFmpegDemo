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
SDL_Surface *hello = NULL;

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

bool loadMedia() {
    bool success = true;
    const std::string resPath = getResourcePath("l2") + "hello_world.bmp";
    hello = SDL_LoadBMP(resPath.c_str());
    if (hello == NULL) {
        printf("Unable to load iamge %s!SDL Error:%s\n", resPath.c_str(), SDL_GetError());
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
    } else {
        if (!loadMedia()) {
            printf("Failed to laod media!\n");
        } else {
            SDL_BlitSurface(hello, NULL, surface, NULL);
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
        }
    }
    close();

    return 0;
}