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
LTexture spriteSheetTexture;

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
    const std::string resPath = getResourcePath("l11") + "dots.png";

    if (!spriteSheetTexture.loadFromFile(resPath, renderer)) {
        printf("Failed to load sprite sheet texture image!SDL Error:%s\n", IMG_GetError());
        success = false;
    } else {
        spriteClips[0].x = 0;
        spriteClips[0].y = 0;
        spriteClips[0].w = 100;
        spriteClips[0].h = 100;

        spriteClips[1].x = 100;
        spriteClips[1].y = 0;
        spriteClips[1].w = 100;
        spriteClips[1].h = 100;

        spriteClips[2].x = 0;
        spriteClips[2].y = 100;
        spriteClips[2].w = 100;
        spriteClips[2].h = 100;

        spriteClips[3].x = 100;
        spriteClips[3].y = 100;
        spriteClips[3].w = 100;
        spriteClips[3].h = 100;
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
            while (!quit) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                spriteSheetTexture.render(0, 0, renderer, &spriteClips[0]);
                spriteSheetTexture.render(SCREEN_WIDTH - spriteClips[1].w, 0, renderer, &spriteClips[1]);
                //Render bottom left sprite
                spriteSheetTexture.render(0, SCREEN_HEIGHT - spriteClips[2].h, renderer, &spriteClips[2]);
                //Render bottom right sprite
                spriteSheetTexture.render(SCREEN_WIDTH - spriteClips[3].w, SCREEN_HEIGHT - spriteClips[3].h, renderer,
                                          &spriteClips[3]);
                SDL_RenderPresent(renderer);
            }
        }
    }
    close();
    return 0;
}