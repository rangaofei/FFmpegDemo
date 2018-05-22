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

bool init();

bool loadMedia();

void close();


SDL_Window *window = NULL;

SDL_Renderer *renderer = NULL;

TTF_Font *font = NULL;

LTexture promptTextTexture;
LTexture inputTextTexture;


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
    bool success = true;
    const std::string ttf = getResourcePath("l32") + "lazy.ttf";
    font = TTF_OpenFont(ttf.c_str(), 28);

    if (font == NULL) {
        printf("Failed to load lazy font! SDL_ttf Error:%s\n", TTF_GetError());
        success = false;
    } else {
        SDL_Color textColor = {0, 0, 0, 0xFF};
        if (!promptTextTexture.loadFromRenderedText("Enter Text:", textColor, font, renderer)) {
            printf("Failed to render prompt text!\n");
            success = false;
        }
    }
    return success;
}

void close() {
    promptTextTexture.free();
    inputTextTexture.free();
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
            std::string inputText = "Some Text";
            inputTextTexture.loadFromRenderedText(inputText.c_str(), textColor, font, renderer);

            SDL_StartTextInput();
            while (!quit) {
                bool renderText = false;
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
                            inputText.pop_back();
                            renderText = true;
                        } else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                            SDL_SetClipboardText(inputText.c_str());
                        } else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                            inputText = SDL_GetClipboardText();
                            renderText = true;
                        }
                    } else if (e.type == SDL_TEXTINPUT) {
                        if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') &&
                              (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {
                            inputText += e.text.text;
                            renderText = true;
                        }
                    }
                }

                if (renderText) {
                    if (inputText != "") {
                        inputTextTexture.loadFromRenderedText(inputText.c_str(), textColor, font, renderer);
                    } else {
                        inputTextTexture.loadFromRenderedText(" ", textColor, font, renderer);
                    }
                }

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                promptTextTexture.render((SCREEN_WIDTH - promptTextTexture.getWidth()) / 2, 0, renderer);
                inputTextTexture.render((SCREEN_WIDTH - inputTextTexture.getWidth()) / 2, promptTextTexture.getHeight(),
                                        renderer);

                SDL_RenderPresent(renderer);
            }
        }
    }
    close();
    return 0;
}