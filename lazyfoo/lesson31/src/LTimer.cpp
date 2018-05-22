//
// Created by saka on 18-5-22.
//

#include <SDL2/SDL_timer.h>
#include "LTimer.h"

LTimer::LTimer() {
    startTicks = 0;
    started = false;
}

void LTimer::start() {
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
}

void LTimer::stop() {
    started = false;
    paused = false;
    startTicks = 0;
    pausedTicks = 0;

}

void LTimer::pause() {
    if (started && !paused) {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }

}

void LTimer::unpause() {
    if (started && paused) {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }

}

Uint32 LTimer::getTicks() {
    Uint32 time = 0;
    if (started) {
        if (paused) {
            time = pausedTicks;
        } else {
            time = SDL_GetTicks() - startTicks;
        }
    }
    return time;
}

bool LTimer::isStarted() {
    return started;
}

bool LTimer::isPaused() {
    return paused;
}
