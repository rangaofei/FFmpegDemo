//
// Created by saka on 18-5-21.
//

#include "LButton.h"
#include "../../lesson13/src/LTexture.h"

LButton::LButton() {
    position.x = 0;
    position.y = 0;
    currentSprite = BUTTON_SPRITE_MOUSE_OUT;

}

void LButton::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void LButton::handleEvent(SDL_Event *e) {
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN ||
        e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if (x < position.x) {
            inside = false;
        } else if (x > position.x + BUTTON_WIDTH) {
            inside = false;
        } else if (y < position.y) {
            inside = false;
        } else if (y > position.y + BUTTON_HEIGHT) {
            inside = false;
        }
        if (!inside) {
            currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        } else {
            switch (e->type) {
                case SDL_MOUSEMOTION:
                    currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                case SDL_MOUSEBUTTONUP:
                    currentSprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}

void LButton::render(SDL_Renderer *renderer, LTexture *buttonSpriteSheetTexture, SDL_Rect *spriteClips) {
    buttonSpriteSheetTexture->render(position.x, position.y, renderer, &spriteClips[currentSprite]);
}
