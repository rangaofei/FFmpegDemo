//
// Created by saka on 18-5-18.
//

#include <SDL2/SDL.h>
#include "cleanup.h"
#include "res_path.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


void logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *ren) {
    SDL_Texture *texture = nullptr;
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

    if (loadedImage != nullptr) {
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        SDL_free(loadedImage);
        if (texture == nullptr) {
            logSDLError(std::cout, "CreateTextureFromSurface");
        }
    } else {
        logSDLError(std::cout, "LoadBMP");
    }
    return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;

    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logSDLError(std::cout, "SDL_init");
    }
    SDL_Window *window = SDL_CreateWindow("Lesson2", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        logSDLError(std::cout, "CreateRenderer");
        cleanup(window);
        SDL_Quit();
        return 1;
    }

    const std::string resPath = getResourcePath("Lesson2");
    SDL_Texture *background = loadTexture(resPath + "background.bmp", renderer);
    SDL_Texture *image = loadTexture(resPath + "image.bmp", renderer);
    if (background == nullptr || image == nullptr) {
        cleanup(background,image,renderer,window);
        SDL_Quit();
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        SDL_RenderClear(renderer);
        int bW, bH;
        SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
        renderTexture(background, renderer, 0, 0);
        renderTexture(background, renderer, bW, 0);
        renderTexture(background, renderer, 0, bH);
        renderTexture(background, renderer, bW, bH);

        int iW, iH;
        SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
        int x = SCREEN_WIDTH / 2 - iW / 2;
        int y = SCREEN_HEIGHT / 2 - iH / 2;
        renderTexture(image, renderer, x, y);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }

    cleanup(background, image, renderer, window);
    SDL_Quit();
}