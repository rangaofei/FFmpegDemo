//
// Created by saka on 18-5-22.
//

#include "Dot.h"
#include "LTexture.h"

Dot::Dot(int x, int y) {
    posX = x;
    posY = y;

    colliders.resize(11);

    velX = 0;
    velY = 0;

    colliders[0].w = 6;
    colliders[0].h = 1;

    colliders[1].w = 10;
    colliders[1].h = 1;

    colliders[2].w = 14;
    colliders[2].h = 1;

    colliders[3].w = 16;
    colliders[3].h = 2;

    colliders[4].w = 18;
    colliders[4].h = 2;

    colliders[5].w = 20;
    colliders[5].h = 6;

    colliders[6].w = 18;
    colliders[6].h = 2;

    colliders[7].w = 16;
    colliders[7].h = 2;

    colliders[8].w = 14;
    colliders[8].h = 1;

    colliders[9].w = 10;
    colliders[9].h = 1;

    colliders[10].w = 6;
    colliders[10].h = 1;

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
    texture->render(posX, posY, renderer);
}


void Dot::move(std::vector<SDL_Rect> &otherColliders) {
    posX += velX;
    shiftColliders();
    if (posX < 0 || (posX + DOT_WIDTH > SCREEN_WIDTH)
        || checkCollision(colliders, otherColliders)) {
        posX -= velX;
        shiftColliders();
    }
    posY += velY;
    shiftColliders();

    if (posY < 0 || (posY + DOT_HEIGHT > SCREEN_HEIGHT)
        || checkCollision(colliders, otherColliders)) {
        posY -= velY;
        shiftColliders();
    }

}

std::vector<SDL_Rect> &Dot::getColliders() {
    return colliders;
}

void Dot::shiftColliders() {
    int r = 0;
    for (int set = 0; set < colliders.size(); ++set) {
        colliders[set].x = posX + (DOT_WIDTH - colliders[set].w) / 2;
        colliders[set].y = posY + r;
        r += colliders[set].h;
    }

}

bool Dot::checkCollision(std::vector<SDL_Rect> &a, std::vector<SDL_Rect> &b) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    for (int Abox = 0; Abox < a.size(); Abox++) {
        leftA = a[Abox].x;
        rightA = a[Abox].x + a[Abox].w;
        topA = a[Abox].y;
        bottomA = a[Abox].y + a[Abox].h;

        for (int Bbox = 0; Bbox < b.size(); Bbox++) {
            leftB = b[Bbox].x;
            rightB = b[Bbox].x + b[Bbox].w;
            topB = b[Bbox].y;
            bottomB = b[Bbox].y + b[Bbox].h;

            if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false) {
                return true;
            }
        }
    }

    return false;
}
