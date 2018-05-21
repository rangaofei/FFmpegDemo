//
// Created by saka on 18-5-21.
//

#ifndef FFMPEGDEMO_LTEXTURE_H
#define FFMPEGDEMO_LTEXTURE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class LTexture {

public:
    LTexture();

    ~LTexture();

    bool loadFromFile(std::string path, SDL_Renderer *renderer);

    void free();

    void render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip = NULL);

    int getWidth();

    int getHeight();

private:
    SDL_Texture *texture;
    int width;
    int height;
};


#endif //FFMPEGDEMO_LTEXTURE_H
