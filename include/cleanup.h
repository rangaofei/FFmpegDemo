//
// Created by saka on 18-5-18.
//

#ifndef SDLDEMO_CLEANUP_H
#define SDLDEMO_CLEANUP_H

#include <utility>
#include <SDL2/SDL.h>

template<typename T, typename...Args>
void cleanup(T *t, Args &&... args) {
    cleanup(t);
    cleanup(std::forward<Args>(args)...);
};

template<>
inline void cleanup<SDL_Window>(SDL_Window *win) {
    if (!win) {
        return;
    }
    SDL_DestroyWindow(win);
}

template<>
inline void cleanup<SDL_Renderer>(SDL_Renderer *ren) {
    if (!ren) {
        return;
    }
    SDL_DestroyRenderer(ren);
}

template<>
inline void cleanup<SDL_Texture>(SDL_Texture *tex) {
    if (!tex) {
        return;
    }
    SDL_DestroyTexture(tex);
}

template<>
inline void cleanup<SDL_Surface>(SDL_Surface *sur) {
    if (!sur) {
        return;
    }
    SDL_FreeSurface(sur);
}

#endif //SDLDEMO_CLEANUP_H
