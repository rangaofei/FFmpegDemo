//
// Created by saka on 18-5-22.
//

#include "Dot.h"
#include "LTexture.h"

Dot::Dot() {
    posX = 0;
    posY = 0;

    velX = 0;
    velY = 0;
}

void Dot::handleEvent(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                velY -= DOT_VEL;
                break;
            case SDLK_DOWN:
                velY += DOT_VEL;
                break;
            case SDLK_LEFT:
                velX -= DOT_VEL;
                break;
            case SDLK_RIGHT:
                velX += DOT_VEL;
                break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                velY += DOT_VEL;
                break;
            case SDLK_DOWN:
                velY -= DOT_VEL;
                break;
            case SDLK_LEFT:
                velX += DOT_VEL;
                break;
            case SDLK_RIGHT:
                velX -= DOT_VEL;
                break;
        }
    }

}


void Dot::render(LTexture *dotTexture, SDL_Renderer *renderer, int camX, int camY) {
    dotTexture->render(posX - camX, posY - camY, renderer);
}


void Dot::move() {
    posX += velX;
    if (posX < 0 || (posX + DOT_WIDTH > SCREEN_WIDTH)) {
        posX -= velX;
    }
    posY += velY;

    if (posY < 0 || (posY + DOT_HEIGHT > SCREEN_HEIGHT)) {
        posY -= velY;
    }
}

int Dot::getPosX() {
    return posX;
}

int Dot::getPosY() {
    return posY;
}


