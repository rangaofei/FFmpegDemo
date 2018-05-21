//
// Created by saka on 18-5-21.
//

#include <SDL2/SDL.h>
#include "LTexture.h"
#include "res_path.h"
#include "LButton.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


const int TOTAL_BUTTONS = 4;


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

TTF_Font *font = NULL;

SDL_Rect spriteClips[BUTTON_SPRITE_TOTAL];

LTexture buttonSpriteSheetTexture;
LButton buttons[TOTAL_BUTTONS];

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

    const std::string resPath = getResourcePath("l17") + "button.png";
    if (!buttonSpriteSheetTexture.loadFromFile(resPath, renderer)) {
        printf("Failed to load button sprite texture!\n");
        success = false;
    } else {
        for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
            spriteClips[i].x = 0;
            spriteClips[i].y = i * 200;
            spriteClips[i].w = BUTTON_WIDTH;
            spriteClips[i].h = BUTTON_HEIGHT;
        }
        buttons[0].setPosition(0, 0);
        buttons[1].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, 0);
        buttons[2].setPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
        buttons[3].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
    }
    return success;
}

void close() {
    buttonSpriteSheetTexture.free();

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

                    for (int i = 0; i < TOTAL_BUTTONS; i++) {
                        buttons[i].handleEvent(&e);
                    }
                }

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                for (int i = 0; i < TOTAL_BUTTONS; i++) {
                    buttons[i].render(renderer, &buttonSpriteSheetTexture, spriteClips);
                }
                SDL_RenderPresent(renderer);
            }

        }
    }

    close();

    return 0;
}