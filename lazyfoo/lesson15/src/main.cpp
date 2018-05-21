//
// Created by saka on 18-5-21.
//

#include <SDL2/SDL.h>
#include "LTexture.h"
#include "res_path.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect spriteClips[WALKING_ANIMATION_FRAMES];
LTexture arrowTexture;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

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
    const std::string resPath = getResourcePath("l15") + "arrow.png";

    if (!arrowTexture.loadFromFile(resPath, renderer)) {
        printf("Failed to load walking animation texture!\n");
        success = false;
    }
    return success;
}

void close() {
    arrowTexture.free();
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

            double degrees = 0;
            SDL_RendererFlip flipType = SDL_FLIP_NONE;

            while (!quit) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                            case SDLK_a:
                                degrees -= 60;
                                break;
                            case SDLK_d:
                                degrees += 60;
                                break;
                            case SDLK_q:
                                flipType = SDL_FLIP_HORIZONTAL;
                                break;
                            case SDLK_w:
                                flipType = SDL_FLIP_NONE;
                                break;
                            case SDLK_e:
                                flipType = SDL_FLIP_VERTICAL;
                                break;
                        }
                    }
                }

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                arrowTexture.render((SCREEN_WIDTH - arrowTexture.getWidth()) / 2,
                                    (SCREEN_HEIGHT - arrowTexture.getHeight()) / 2, renderer, NULL, degrees, NULL,
                                    flipType);
                SDL_RenderPresent(renderer);
            }
        }
    }
    close();
    return 0;
}