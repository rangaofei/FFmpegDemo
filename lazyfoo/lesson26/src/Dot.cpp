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

void Dot::render(LTexture *texture, SDL_Renderer *renderer) {
    texture->render(posX, posY, renderer);
}
