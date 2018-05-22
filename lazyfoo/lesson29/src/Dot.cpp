//
// Created by saka on 18-5-22.
//

#include "Dot.h"
#include "LTexture.h"

Dot::Dot(int x, int y) {
    posX = x;
    posY = y;

    collider.r = DOT_WIDTH / 2;

    velX = 0;
    velY = 0;

    shiftColliders();
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


void Dot::render(LTexture *texture, SDL_Renderer *renderer) {
    texture->render(posX - collider.r, posY - collider.r, renderer);
}


void Dot::shiftColliders() {
    collider.x = posX;
    collider.y = posY;
}


void Dot::move(SDL_Rect &square, Circle &circle) {
    posX += velX;
    shiftColliders();
    if (posX < 0 || (posX + DOT_WIDTH > SCREEN_WIDTH)
        || checkCollision(collider, square) || checkCollision(collider, circle)) {
        posX -= velX;
        shiftColliders();
    }
    posY += velY;
    shiftColliders();

    if (posY < 0 || (posY + DOT_HEIGHT > SCREEN_HEIGHT)
        || checkCollision(collider, square) || checkCollision(collider, circle)) {
        posY -= velY;
        shiftColliders();
    }
}

Circle &Dot::getCollider() {
    return collider;
}

bool Dot::checkCollision(Circle &a, Circle &b) {
    int totalRadiusSquared = a.r + b.r;
    totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    if (distanceSquared(a.x, a.y, b.x, b.y) < totalRadiusSquared) {
        return true;
    }
    return false;
}

bool Dot::checkCollision(Circle &a, SDL_Rect &b) {
    int cX, cY;
    if (a.x < b.x) {
        cX = b.x;
    } else if (a.x > b.x + b.w) {
        cX = b.x + b.w;
    } else {
        cX = a.x;
    }

    if (a.y < b.y) {
        cY = b.y;
    } else if (a.y > b.y + b.h) {
        cY = b.y + b.h;
    } else {
        cY = a.y;
    }

    if (distanceSquared(a.x, a.y, cX, cY) < a.r * a.r) {
        return true;
    }
    return false;
}

double Dot::distanceSquared(int x1, int y1, int x2, int y2) {
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    return deltaX * deltaX + deltaY * deltaY;
}
