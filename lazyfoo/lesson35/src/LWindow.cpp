//
// Created by saka on 18-5-22.
//

#include "LWindow.h"

LWindow::LWindow() {
    window = NULL;
    mouseFocus = false;
    keyBoardFocus = false;
    fullScreen = false;
    minimized = false;
    width = 0;
    height = 0;

}

bool LWindow::init() {
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window != NULL) {
        mouseFocus = false;
        keyBoardFocus = true;
        width = SCREEN_WIDTH;
        height = SCREEN_HEIGHT;
    }
    return window != NULL;
}

SDL_Renderer *LWindow::createRenderer() {
    return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void LWindow::handleEvent(SDL_Event &e) {
    bool updateCaption = false;
    width = e.window.data1;
    height = e.window.data2;
//    SDL_RenderPresent();

}

void LWindow::free() {

}

int LWindow::getWidth() {
    return 0;
}

int LWindow::getHeight() {
    return 0;
}

bool LWindow::hasMouseFocus() {
    return false;
}

bool LWindow::hasKeyboardFocus() {
    return false;
}

bool LWindow::isMinized() {
    return false;
}
