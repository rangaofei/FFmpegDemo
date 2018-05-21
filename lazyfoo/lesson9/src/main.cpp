//
// Created by saka on 18-5-20.
//

#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "res_path.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

bool init();

bool loadMedia();

void close();


SDL_Texture *loadTexture(std::string path);

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
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL) {
                printf("Renderer could not be created!SDL Error:%s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error:%s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

SDL_Texture *loadTexture(std::string path) {
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s!SDL Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error:%s\n", path.c_str());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}


bool loadMedia() {
    bool success = true;
    const std::string resPath = getResourcePath("l9") + "viewport.png";
    texture = loadTexture(resPath);
    if (texture == NULL) {
        printf("Failed to load texture image!\n");
        success = false;
    }
    return success;
}

void close() {
    SDL_DestroyTexture(texture);
    texture = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;
    IMG_Quit();
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
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            SDL_Rect topLeftViewport;
            topLeftViewport.x = 0;
            topLeftViewport.y = 0;
            topLeftViewport.w = SCREEN_WIDTH / 2;
            topLeftViewport.h = SCREEN_HEIGHT / 2;
            SDL_RenderSetViewport(renderer, &topLeftViewport);

            SDL_RenderCopy(renderer, texture, NULL, NULL);

            SDL_Rect topRightViewport;
            topRightViewport.x = SCREEN_WIDTH / 2;
            topRightViewport.y = 0;
            topRightViewport.w = SCREEN_WIDTH / 2;
            topRightViewport.h = SCREEN_HEIGHT / 2;
            SDL_RenderSetViewport(renderer, &topRightViewport);

            SDL_RenderCopy(renderer, texture, NULL, NULL);

            SDL_Rect bottomViewport;
            bottomViewport.x = 0;
            bottomViewport.y = SCREEN_HEIGHT / 2;
            bottomViewport.w = SCREEN_WIDTH;
            bottomViewport.h = SCREEN_HEIGHT / 2;
            SDL_RenderSetViewport(renderer, &bottomViewport);

            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }

    }

    close();

    return 0;
}