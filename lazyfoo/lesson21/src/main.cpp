//
// Created by saka on 18-5-21.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "LTexture.h"
#include "res_path.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Mix_Music *music = NULL;

Mix_Chunk *scratch = NULL;
Mix_Chunk *high = NULL;
Mix_Chunk *medium = NULL;
Mix_Chunk *low = NULL;

bool init();

bool loadMedia();

void close();

SDL_Window *window = NULL;

SDL_Renderer *renderer = NULL;

LTexture promptTexture;


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
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    printf("SDL_mixer could not initialize!SDL_mixer Error:%s\n", Mix_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;
    const std::string prompt = getResourcePath("l21") + "prompt.png";
    if (!promptTexture.loadFromFile(prompt, renderer)) {
        printf("Failed to load prompt texture!\n");
        success = false;
    }
    const std::string str_beat = getResourcePath("l21") + "beat.wav";
    music = Mix_LoadMUS(str_beat.c_str());
    if (music == NULL) {
        printf("Failed to load beat music!SDL_mixer Error:%s\n", Mix_GetError());
        success = false;
    }
    const std::string str_scratch = getResourcePath("l21") + "scratch.wav";
    scratch = Mix_LoadWAV(str_scratch.c_str());
    if (scratch == NULL) {
        printf("Failed to load scratch music!SDL_mixer Error:%s\n", Mix_GetError());
        success = false;
    }
    const std::string str_high = getResourcePath("l21") + "high.wav";
    high = Mix_LoadWAV(str_high.c_str());
    if (high == NULL) {
        printf("Failed to load high music!SDL_mixer Error:%s\n", Mix_GetError());
        success = false;
    }
    const std::string str_low = getResourcePath("l21") + "low.wav";
    low = Mix_LoadWAV(str_low.c_str());
    if (music == NULL) {
        printf("Failed to load low music!SDL_mixer Error:%s\n", Mix_GetError());
        success = false;
    }
    const std::string str_medium = getResourcePath("l21") + "medium.wav";
    medium = Mix_LoadWAV(str_medium.c_str());
    if (music == NULL) {
        printf("Failed to load  medium music!SDL_mixer Error:%s\n", Mix_GetError());
        success = false;
    }
    return success;
}

void close() {
    promptTexture.free();
    Mix_FreeChunk(scratch);
    Mix_FreeChunk(high);
    Mix_FreeChunk(low);
    Mix_FreeChunk(medium);
    Mix_FreeMusic(music);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_Quit();
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
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                            case SDLK_1:
                                Mix_PlayChannel(-1, high, 0);
                                break;
                            case SDLK_2:
                                Mix_PlayChannel(-1, medium, 0);
                                break;
                            case SDLK_3:
                                Mix_PlayChannel(-1, low, 0);
                                break;
                            case SDLK_4:
                                Mix_PlayChannel(-1, scratch, 0);
                                break;
                            case SDLK_9:
                                if (Mix_PlayingMusic() == 0) {
                                    Mix_PlayMusic(music, -1);
                                } else {
                                    if (Mix_PlayingMusic() == 1) {
                                        Mix_ResumeMusic();
                                    } else {
                                        Mix_PauseMusic();
                                    }
                                }
                                break;
                            case SDLK_0:
                                Mix_HaltMusic();
                                break;
                        }
                    }
                }
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                promptTexture.render(0, 0, renderer);

                SDL_RenderPresent(renderer);
            }
        }
    }
    close();
    return 0;
}