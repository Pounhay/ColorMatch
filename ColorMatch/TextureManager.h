#pragma once

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cmath>
#include <string>

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
};
