//
// Created by saka on 18-5-21.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include "LTexture.h"
#include "res_path.h"
#include "LTimer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int SCREEN_FPS = 30;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;


bool init();

bool loadMedia();

void close();

SDL_Window *window = NULL;

SDL_Renderer *renderer = NULL;

TTF_Font *font = NULL;

LTexture fpsTextTexture;


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
                if (TTF_Init() == -1) {
                    printf("SDL_ttf could not initialize! SDL_ttf Error:%s\n", TTF_GetError());
                }
            }
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;
    const std::string ttf = getResourcePath("l23") + "lazy.ttf";
    font = TTF_OpenFont(ttf.c_str(), 28);
    if (font == NULL) {
        printf("Failed to load lazy font! SDL_ttf Error:%s\n", TTF_GetError());
        success = false;
    }

    return success;
}

void close() {
    fpsTextTexture.free();
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

            SDL_Color textColor = {0, 0, 0, 255};

            LTimer fpsTimer;
            LTimer capTimer;

            std::stringstream timeText;

            int countedFrames = 0;
            fpsTimer.start();
            while (!quit) {
                capTimer.start();
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
                float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
                if (avgFPS > 2000000) {
                    avgFPS = 0;
                }
                timeText.str("");
                timeText << "Average Frames Per Second(with cap) " << avgFPS;


                if (!fpsTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor, font, renderer)) {
                    printf("Unable to render time texture!\n");
                }

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                fpsTextTexture.render((SCREEN_WIDTH - fpsTextTexture.getWidth()) / 2,
                                      (SCREEN_HEIGHT - fpsTextTexture.getHeight()) / 2, renderer);
                SDL_RenderPresent(renderer);

                ++countedFrames;

                int frameTicks = capTimer.getTicks();
                if (frameTicks < SCREEN_TICK_PER_FRAME) {
                    SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
                }
            }
        }
    }
    close();
    return 0;
}