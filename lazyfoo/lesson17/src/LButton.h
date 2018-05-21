//
// Created by saka on 18-5-21.
//

#ifndef FFMPEGDEMO_LBUTTON_H
#define FFMPEGDEMO_LBUTTON_H


#include <SDL2/SDL_events.h>
#include "LTexture.h"


const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;

enum LButtonSprite {
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};


class LButton {
public:
    LButton();

    void setPosition(int x, int y);

    void handleEvent(SDL_Event *e);

    void render(SDL_Renderer *renderer, LTexture *buttonSpriteSheetTexture, SDL_Rect *spriteClips);

private:
    SDL_Point position;
    LButtonSprite currentSprite;

};


#endif //FFMPEGDEMO_LBUTTON_H
