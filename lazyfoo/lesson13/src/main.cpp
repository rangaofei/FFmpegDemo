//
// Created by saka on 18-5-21.
//

#include "LTexture.h"
#include "res_path.h"
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();

bool loadMedia();

void close();

SDL_Window *window = NULL;

SDL_Renderer *renderer = NULL;

SDL_Rect spriteClips[4];
LTexture modulatedTexture;
LTexture backgroundTexture;

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize!SDK Error:%s\n", SDL_GetError());
        success = false;
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning:Linear texture filtering not enabled!");
        }
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be crated!SDL Error:%s\n", SDL_GetError());
            success = false;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                printf("Render could not be created!SDL Error:%s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize!SDL_iamge errorL%s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;
    const std::string resPath = getResourcePath("l13") + "fadeout.png";

    if (!modulatedTexture.loadFromFile(resPath, renderer)) {
        printf("Failed to load front texture!\n", IMG_GetError());
        success = false;
    } else {
        modulatedTexture.setBlendMode(SDL_BLENDMODE_BLEND);
    }
    const std::string backPath = getResourcePath("l13") + "fadein.png";
    if (!backgroundTexture.loadFromFile(backPath, renderer)) {
        printf("Failed to load background texture!\n");
        success = false;
    }
    return success;
}

void close() {
    modulatedTexture.free();
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argsp[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            bool quit = false;
            SDL_Event e;

            Uint8 a = 255;

            while (!quit) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        if (e.key.keysym.sym == SDLK_w) {
                            if (a + 32 > 255) {
                                a = 255;
                            } else {
                                a += 32;
                            }
                        } else if (e.key.keysym.sym == SDLK_s) {
                            if (a - 32 < 0) {
                                a = 0;
                            } else {
                                a -= 32;
                            }
                        }
                    }
                }

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                backgroundTexture.render(0, 0, renderer);
                
                modulatedTexture.setAlpha(a);
                modulatedTexture.render(0, 0, renderer);
                SDL_RenderPresent(renderer);
            }
        }
    }
    close();
    return 0;
}