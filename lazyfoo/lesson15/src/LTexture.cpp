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
    bool result = (texture != NULL);
    return result;
}

void LTexture::free() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}


void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(texture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(texture, blending);

}


void LTexture::render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip, double angle,
                      SDL_Point *center, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = {x, y, width, height};
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

void LTexture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture, alpha);
}

int LTexture::getWidth() {
    return width;
}

int LTexture::getHeight() {
    return height;
}