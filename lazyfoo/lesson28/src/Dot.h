//
// Created by saka on 18-5-22.
//

#ifndef FFMPEGDEMO_DOT_H
#define FFMPEGDEMO_DOT_H


#include <SDL2/SDL_events.h>
#include <vector>
#include "LTexture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Dot {
public:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    static const int DOT_VEL = 1;

    Dot(int x, int y);

    void handleEvent(SDL_Event &e);

    void move(std::vector<SDL_Rect> &otherColliders);

    void render(LTexture *texture, SDL_Renderer *renderer);

    bool checkCollision(std::vector<SDL_Rect> &a, std::vector<SDL_Rect> &b);

    std::vector<SDL_Rect> &getColliders();

private:
    int posX, posY;
    int velX, velY;
    std::vector<SDL_Rect> colliders;

    void shiftColliders();

};


#endif //FFMPEGDEMO_DOT_H
