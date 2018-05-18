//
// Created by saka on 18-5-18.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "res_path.h"
#include "cleanup.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;
const int TILE_SIZE = 40;


void logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr) {

    SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != nullptr) {
        dst.w = clip->w;
        dst.h = clip->h;
    } else {
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    }
    renderTexture(tex, ren, dst, clip);
}

SDL_Texture *renderText(const std::string &message, const std::string &fontFile,
                        SDL_Color color, int fontSize, SDL_Renderer *renderer) {
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr) {
        logSDLError(std::cout, "TTF_OpenFont");
        return nullptr;
    }

    SDL_Surface *sur = TTF_RenderText_Blended(font, message.c_str(), color);
    if (sur == nullptr) {
        TTF_CloseFont(font);
        logSDLError(std::cout, "TTF_RenderText");
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, sur);
    if (texture == nullptr) {
        logSDLError(std::cout, "CreateTexture");
    }
    SDL_FreeSurface(sur);
    TTF_CloseFont(font);
    return texture;
}


int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logSDLError(std::cout, "SDL_init");
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Lesson6", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() != 0) {
        logSDLError(std::cout, "TTF_Init");
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        logSDLError(std::cout, "IMG_Init");
        cleanup(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        logSDLError(std::cout, "CreateRenderer");
        cleanup(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    const std::string resPath = getResourcePath("Lesson6");
//We'll render the string "TTF fonts are cool!" in white
//Color is in RGBA format
    SDL_Color color = {255, 255, 255, 255};
    SDL_Texture *image = renderText("TTF fonts are cool!", resPath + "sample.ttf",
                                    color, 64, renderer);
    if (image == nullptr) {
        cleanup(image, renderer, window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
//Get the texture w/h so we can center it in the screen
    int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }
        SDL_RenderClear(renderer);

        renderTexture(image, renderer, x, y);

        SDL_RenderPresent(renderer);
    }

    cleanup(image, renderer, window);
    IMG_Quit();
    SDL_Quit();
}