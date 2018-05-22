//
// Created by saka on 18-5-22.
//

#include "Dot.h"
#include "LTexture.h"

Dot::Dot() {
    posX = 0;
    posY = 0;

    collider.w = DOT_WIDTH;
    collider.h = DOT_HEIGHT;

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

void Dot::move(SDL_Rect &wall) {
    posX += velX;
    collider.x = posX;
    if (posX < 0 || (posX + DOT_WIDTH > SCREEN_WIDTH)
        || checkCollision(collider, wall)) {
        posX -= velX;
        collider.x = posX;
    }
    posY += velY;
    collider.y = posY;

    if (posY < 0 || (posY + DOT_HEIGHT > SCREEN_HEIGHT)
        || checkCollision(collider, wall)) {
        posY -= velY;
        collider.y = posY;
    }
}

void Dot::render(LTexture *texture, SDL_Renderer *renderer) {
    texture->render(posX, posY, renderer);
}

bool Dot::checkCollision(SDL_Rect a, SDL_Rect b) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    printf("collide leftA=%d,RightA=%d,topA=%d,bottomA=%d\n", leftA, rightA, topA, bottomA);
    printf("wall    leftB=%d,RightB=%d,topB=%d,bottomB=%d\n", leftB, rightB, topB, bottomB);
    if (bottomA <= topB) {
        return false;
    }
    if (topA >= bottomB) {
        return false;
    }

    if (rightA <= leftB) {
        return false;
    }

    if (leftA >= rightB) {
        return false;
    }
    return true;
}
