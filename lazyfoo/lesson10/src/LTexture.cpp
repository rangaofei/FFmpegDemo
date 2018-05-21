//
// Created by saka on 18-5-21.
//

#include "LTexture.h"


LTexture::LTexture() {
    texture = NULL;
    width = 0;
    height = 0;
}

LTexture::~LTexture() {
    free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer *renderer) {
    free();
    SDL_Texture *newTexture = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL) {
        printf("Unable to load image %s!SDL Error:%s\n", path.c_str(), SDL_GetError());
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0X00, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s!SDL Error:%s\n", path.c_str(), SDL_GetError());
        } else {
            width = loadedSurface->w;
            height = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    texture = newTexture;
    return texture != NULL;
}

void LTexture::free() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void LTexture::render(int x, int y, SDL_Renderer *renderer) {
    SDL_Rect renderQuad = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

int LTexture::getWidth() {
    return width;
}

int LTexture::getHeight() {
    return height;
}

