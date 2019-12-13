#pragma once

#include "TextureManager.h"

class GameObject
{
	int xpos, ypos;
	int h1, w1;

	SDL_Texture* objTexture;
	SDL_Rect scrRect, destRect;
	SDL_Renderer* renderer;

public:
	GameObject() {}
	~GameObject() {};

	//Constructor de GameOBject
	GameObject(const char* s, int x, int y, int w, int h, SDL_Renderer* ren) {
		xpos = x;
		ypos = y;
		h1 = h;
		w1 = w;
		renderer = ren;
		objTexture = TextureManager::LoadTexture(s, renderer);
	}

	//Maneja las actualizaciones
	void Update()
	{
		scrRect.w = w1;
		scrRect.h = h1;
		scrRect.x = 0;
		scrRect.y = 0;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = scrRect.w;
		destRect.h = scrRect.h;
	}

	//Maneja el renderizado de las imagenes
	void Render() {
		SDL_RenderCopy(renderer, objTexture, &scrRect, &destRect);
	}
};