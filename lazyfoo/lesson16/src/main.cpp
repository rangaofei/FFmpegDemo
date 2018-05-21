//
// Created by saka on 18-5-21.
//

#include <SDL2/SDL.h>
#include "LTexture.h"
#include "res_path.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

TTF_Font *font = NULL;

LTexture buttonSpriteSheetTexture;

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
                if (TTF_Init() == -1) {
                    printf("SDL_ttf could not initialize! SDL_ttf Error:%s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;

    const std::string resPath = getResourcePath("l16") + "lazy.ttf";
    font = TTF_OpenFont(resPath.c_str(), 28);
    if (font == NULL) {
        printf("Failed to load lazy font!SDL_ttf Error:%s\n", TTF_GetError());
    } else {
        SDL_Color textColor = {0, 0, 0};
        if (!buttonSpriteSheetTexture.loadFromRenderedText("The quick brown fox junmps over the lazy dog", textColor, font,
                                              renderer)) {
            printf("Failed to render text texture!\n");
            success = false;
        }
    }
    return success;
}

void close() {
    buttonSpriteSheetTexture.free();

    TTF_CloseFont(font);

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

                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(renderer);

                    buttonSpriteSheetTexture.render((SCREEN_WIDTH - buttonSpriteSheetTexture.getWidth()) / 2,
                                       (SCREEN_HEIGHT - buttonSpriteSheetTexture.getHeight()) / 2, renderer);
                    SDL_RenderPresent(renderer);
                }
            }
        }
    }
    close();
    return 0;
}