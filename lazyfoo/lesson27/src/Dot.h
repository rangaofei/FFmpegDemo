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

    void move(SDL_Rect& wall);

    void render(LTexture *texture, SDL_Renderer *renderer);

    bool checkCollision(SDL_Rect a, SDL_Rect b);


private:
    int posX, posY;
    int velX, velY;
    SDL_Rect collider;

};


#endif //FFMPEGDEMO_DOT_H
