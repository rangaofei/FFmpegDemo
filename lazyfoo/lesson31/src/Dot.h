//
// Created by saka on 18-5-22.
//

#ifndef FFMPEGDEMO_DOT_H
#define FFMPEGDEMO_DOT_H


#include <SDL2/SDL_events.h>
#include "LTexture.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


class Dot {
public:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    static const int DOT_VEL = 10;

    Dot();

    void handleEvent(SDL_Event &e);

    void move();

    void render(LTexture *dotTexture, SDL_Renderer *renderer);

    int getPosX();

    int getPosY();

private:
    int posX, posY;
    int velX, velY;

};


#endif //FFMPEGDEMO_DOT_H
