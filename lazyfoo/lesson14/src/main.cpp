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
LTexture spriteSheetTexture;

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
    const std::string resPath = getResourcePath("l14") + "foo.png";

    if (!spriteSheetTexture.loadFromFile(resPath, renderer)) {
        printf("Failed to load walking animation texture!\n");
        success = false;
    } else {
        spriteClips[0].x = 0;
        spriteClips[0].y = 0;
        spriteClips[0].w = 64;
        spriteClips[0].h = 205;

        spriteClips[1].x = 64;
        spriteClips[1].y = 0;
        spriteClips[1].w = 64;
        spriteClips[1].h = 205;

        spriteClips[2].x = 128;
        spriteClips[2].y = 0;
        spriteClips[2].w = 64;
        spriteClips[2].h = 205;

        spriteClips[3].x = 196;
        spriteClips[3].y = 0;
        spriteClips[3].w = 64;
        spriteClips[3].h = 205;
    }
    return success;
}

void close() {
    spriteSheetTexture.free();
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

            int frame = 0;

            while (!quit) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                SDL_Rect *currentClip = &spriteClips[frame / 4];
                spriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2,
                                          renderer, currentClip);
                SDL_RenderPresent(renderer);
                ++frame;
                if (frame / 4 >= WALKING_ANIMATION_FRAMES) {
                    frame = 0;
                }
            }
        }
    }
    close();
    return 0;
}