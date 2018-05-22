//
// Created by saka on 18-5-22.
//

#ifndef FFMPEGDEMO_LWINDOW_H
#define FFMPEGDEMO_LWINDOW_H


#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class LWindow {
public:
    LWindow();

    bool init();

    SDL_Renderer *createRenderer();

    void handleEvent(SDL_Event &e);

    void free();

    int getWidth();

    int getHeight();

    bool hasMouseFocus();

    bool hasKeyboardFocus();

    bool isMinized();

private:
    SDL_Window *window;

    int width;
    int height;

    bool mouseFocus;
    bool keyBoardFocus;
    bool fullScreen;
    bool minimized;
};


#endif //FFMPEGDEMO_LWINDOW_H
