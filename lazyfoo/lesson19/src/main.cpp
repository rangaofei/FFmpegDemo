//
// Created by saka on 18-5-21.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include "res_path.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


bool init();

bool loadMedia();

void close();

SDL_Window *window = NULL;

SDL_Renderer *renderer = NULL;

LTexture promptTexture;