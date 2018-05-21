//
// Created by saka on 18-5-18.
//


#include <SDL2/SDL.h>
#include "LTexture.h"
#include "res_path.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


const int TOTAL_BUTTONS = 4;


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

TTF_Font *font = NULL;


LTexture pressTexture;
LTexture upTexture;
LTexture downTexture;
LTexture leftTexture;
LTexture rightTexture;

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
    std::string resPath = getResourcePath("l18") + "press.png";

    if (!pressTexture.loadFromFile(resPath, renderer)) {
        printf("Failed to load press texture\n");
        success = false;
    }

    resPath = getResourcePath("l18") + "up.png";

    if (!upTexture.loadFromFile(resPath, renderer)) {
        printf("Failed to load up texture\n");
        success = false;
    }

    resPath = getResourcePath("l18") + "down.png";

    if (!downTexture.loadFromFile(resPath, renderer)) {
        printf("Failed to load down texture\n");
        success = false;
    }

    resPath = getResourcePath("l18") + "left.png";

    if (!leftTexture.loadFromFile(resPath, renderer)) {
        printf("Failed to load down texture\n");
        success = false;
    }

    resPath = getResourcePath("l18") + "right.png";

    if (!rightTexture.loadFromFile(resPath, renderer)) {
        printf("Failed to load up texture\n");
        success = false;
    }
    return success;
}


void close() {
    pressTexture.free();
    upTexture.free();
    leftTexture.free();
    downTexture.free();

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
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            bool quit = false;
            SDL_Event e;
            LTexture *currentTexture = NULL;
            while (!quit) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
                if (currentKeyStates[SDL_SCANCODE_UP]) {
                    currentTexture = &upTexture;
                } else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
                    currentTexture = &downTexture;
                } else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
                    currentTexture = &leftTexture;
                } else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
                    currentTexture = &rightTexture;
                } else {
                    currentTexture = &pressTexture;
                }

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                currentTexture->render(0, 0, renderer);
                SDL_RenderPresent(renderer);
            }
        }
    }
    close();

    return 0;
}