//
// Created by saka on 18-5-22.
//

#ifndef FFMPEGDEMO_DOT_H
#define FFMPEGDEMO_DOT_H


#include <SDL2/SDL_events.h>
#include "LTexture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct Circle {
    int x, y;
    int r;
};

class Dot {
public:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    static const int DOT_VEL = 1;

    Dot(int x, int y);

    void handleEvent(SDL_Event &e);

    void move(SDL_Rect &square, Circle &circle);

    void render(LTexture *texture, SDL_Renderer *renderer);

    Circle &getCollider();

    bool checkCollision(Circle &a, Circle &b);

    bool checkCollision(Circle &a, SDL_Rect &b);

    double distanceSquared(int x1, int y1, int x2, int y2);

private:
    int posX, posY;
    int velX, velY;
    Circle collider;

    void shiftColliders();

};


#endif //FFMPEGDEMO_DOT_H
