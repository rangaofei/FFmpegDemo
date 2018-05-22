//
// Created by saka on 18-5-21.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include "LTexture.h"
#include "res_path.h"
#include "LTimer.h"
#include "Dot.h"


const int SCREEN_FPS = 30;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;


bool init();

bool loadMedia();

void close();


SDL_Window *window = NULL;

SDL_Renderer *renderer = NULL;

LTexture dotTexture;
LTexture bgTexture;


bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize!SDL Error:%s\n", SDL_GetError());
        success = false;
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning Linear texture filtering not enabled!");
        }
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created!SDL Error:%s\n", SDL_GetError());
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
                    printf("SDL_image could not initialize!SDL_image Error:%s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;
    const std::string dot = getResourcePath("l31") + "dot.bmp";
    if (!dotTexture.loadFromFile(dot, renderer)) {
        printf("Failed to load dot texture!");
        success = false;
    }

    const std::string bg = getResourcePath("l31") + "bg.png";
    if (!bgTexture.loadFromFile(bg, renderer)) {
        printf("Failed to load background trexture!\n");
        success = false;
    }

    return success;
}

void close() {
    dotTexture.free();
    bgTexture.free();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            bool quit = false;
            SDL_Event e;

            Dot dot;
            int scrollingOffset = 0;

            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    dot.handleEvent(e);
                }
                dot.move();

                --scrollingOffset;
                if (scrollingOffset < -bgTexture.getWidth()) {
                    scrollingOffset = 0;
                }

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);
                
                bgTexture.render(scrollingOffset, 0, renderer);
                bgTexture.render(scrollingOffset + bgTexture.getWidth(), 0, renderer);
                dot.render(&dotTexture, renderer);
                SDL_RenderPresent(renderer);
            }
        }
    }
    close();
    return 0;
}