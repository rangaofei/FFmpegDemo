//
// Created by saka on 18-5-21.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include "LTexture.h"
#include "res_path.h"
#include "LTimer.h"



const int TOTAL_DATA = 10;

bool init();

bool loadMedia();

void close();


SDL_Window *window = NULL;

SDL_Renderer *renderer = NULL;

TTF_Font *font = NULL;

LTexture promptTextTexture;
LTexture dataTextures[TOTAL_DATA];

Sint32 data[TOTAL_DATA];


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
                    printf("SDL_ttf could not initialize!Error:%s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia() {

    SDL_Color textColor = {0, 0, 0, 0xFF};
    SDL_Color highlightColor = {0xFF, 0, 0, 0xFF};

    bool success = true;
    const std::string ttf = getResourcePath("l33") + "lazy.ttf";
    font = TTF_OpenFont(ttf.c_str(), 28);

    if (font == NULL) {
        printf("Failed to load lazy font! SDL_ttf Error:%s\n", TTF_GetError());
        success = false;
    } else {
        SDL_Color textColor = {0, 0, 0, 0xFF};
        if (!promptTextTexture.loadFromRenderedText("Enter Data:", textColor, font, renderer)) {
            printf("Failed to render prompt text!\n");
            success = false;
        }
    }

    const std::string f = getResourcePath("l33") + "nums.bin";
    SDL_RWops *file = SDL_RWFromFile(f.c_str(), "r+b");

    if (file == NULL) {
        printf("Warning:Unbale to open file!SDL Error:%s\n", SDL_GetError());
        file = SDL_RWFromFile(f.c_str(), "w+b");
        if (file != NULL) {
            printf("New file created!\n");
            for (int i = 0; i < TOTAL_DATA; ++i) {
                data[i] = i;
                SDL_RWwrite(file, &data[i], sizeof(Sint32), 1);
            }
            SDL_RWclose(file);
        } else {
            printf("Error:Unable to create file!SDL Error:%s\n", SDL_GetError());
            success = false;
        }
    } else {
        printf("Reading file...!\n");
        for (int i = 0; i < TOTAL_DATA; ++i) {
            SDL_RWread(file, &data[i], sizeof(Sint32), 1);
        }
        SDL_RWclose(file);
    }

    dataTextures[0].loadFromRenderedText(std::to_string((long long) data[0]), highlightColor, font, renderer);

    for (int i = 1; i < TOTAL_DATA; i++) {
        dataTextures[i].loadFromRenderedText(std::to_string((long long) data[i]), textColor, font, renderer);
    }

    return success;
}

void close() {
    const std::string f = getResourcePath("l33") + "nums.bin";
    SDL_RWops *file = SDL_RWFromFile(f.c_str(), "w+b");
    if (file != NULL) {
        for (int i = 0; i < TOTAL_DATA; ++i) {
            SDL_RWwrite(file, &data[i], sizeof(Sint32), 1);
        }
        SDL_RWclose(file);
    } else {
        printf("Error:Unable to save file!%s\n", SDL_GetError());
    }
    promptTextTexture.free();
    for (int i = 0; i < TOTAL_DATA; ++i) {
        dataTextures[i].free();
    }

    TTF_CloseFont(font);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
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

            SDL_Color textColor = {0, 0, 0, 0xFF};
            SDL_Color highlightColor = {0xFF, 0, 0, 0xFF};
            int currentData = 0;

            while (!quit) {
                bool renderText = false;
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                                dataTextures[currentData].loadFromRenderedText(
                                        std::to_string((long long) data[currentData]), textColor, font, renderer
                                );
                                --currentData;
                                if (currentData < 0) {
                                    currentData = TOTAL_DATA - 1;
                                }
                                dataTextures[currentData].loadFromRenderedText(
                                        std::to_string((long long) data[currentData]), highlightColor, font, renderer
                                );
                                break;
                            case SDLK_DOWN:
                                dataTextures[currentData].loadFromRenderedText(
                                        std::to_string((long long) data[currentData]), textColor, font, renderer
                                );
                                ++currentData;
                                if (currentData < 0) {
                                    currentData = TOTAL_DATA - 1;
                                }
                                dataTextures[currentData].loadFromRenderedText(
                                        std::to_string((long long) data[currentData]), highlightColor, font, renderer
                                );
                                break;
                            case SDLK_LEFT:
                                --data[currentData];
                                dataTextures[currentData].loadFromRenderedText(
                                        std::to_string((long long) data[currentData]), highlightColor, font, renderer);
                                break;
                            case SDLK_RIGHT:
                                ++data[currentData];
                                dataTextures[currentData].loadFromRenderedText(
                                        std::to_string((long long) data[currentData]), highlightColor, font, renderer);
                                break;
                        }
                    }
                }

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                promptTextTexture.render((SCREEN_WIDTH - promptTextTexture.getWidth()) / 2, 0, renderer);
                for (int i = 0; i < TOTAL_DATA; ++i) {
                    dataTextures[i].render((SCREEN_WIDTH - dataTextures[i].getWidth()) / 2,
                                           promptTextTexture.getHeight() + dataTextures[0].getHeight() * i, renderer);
                }
                SDL_RenderPresent(renderer);
            }
        }
    }
    close();
    return 0;
}