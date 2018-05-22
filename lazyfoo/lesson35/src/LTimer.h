//
// Created by saka on 18-5-22.
//

#ifndef FFMPEGDEMO_LTIMER_H
#define FFMPEGDEMO_LTIMER_H


#include <SDL2/SDL_types.h>

class LTimer {

public:
    LTimer();

    void start();

    void stop();

    void pause();

    void unpause();

    Uint32 getTicks();

    bool isStarted();

    bool isPaused();

private:
    Uint32 startTicks;
    Uint32 pausedTicks;
    bool paused;
    bool started;
};


#endif //FFMPEGDEMO_LTIMER_H
