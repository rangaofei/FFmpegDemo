//
// Created by saka on 18-5-18.
//

#ifndef SDLDEMO_RES_PATH_H
#define SDLDEMO_RES_PATH_H

#include "Config.h"

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

std::string getResourcePath(const std::string &subDir = "") {
#ifdef _WIN32
    const char PATH_SEP='\\';
#else
    const char PATH_SEP = '/';
#endif

    static std::string baseRes;
    if (baseRes.empty()) {
        char *basePath = SDL_GetBasePath();
        if (basePath) {
            baseRes = basePath;
            SDL_free(basePath);
        } else {
            std::cerr << "Error getting resource path:" << SDL_GetError() << std::endl;
            return "";
        }
#ifdef CLION
        size_t pos = baseRes.rfind("cmake-build-debug");
#else
        size_t pos = baseRes.rfind("build");
#endif
        baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
    }
    return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}

#endif //SDLDEMO_RES_PATH_H
