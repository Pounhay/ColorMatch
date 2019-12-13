#pragma once

#include "GameObject.h"

class Text : public GameObject
{

	SDL_Texture* objTexture;
	SDL_Rect destRect;
	SDL_Renderer* renderer;
	SDL_Texture* Message;	

public:
	int xpos, ypos;
	int h1, w1; 
	SDL_Color color;
	//Constructor de cuadro de texto
	Text() {}
	//Destructor de cuadro de texto
	~Text() {};

	//Inicializa el cuadro de texto
	//@param posicion inicial en x
	//@param posicion inicial en y
	//@param ancho de la caja de texto
	//@param alto de la caja de texto
	//@param Renderer donde se dibujaran las cosas
	Text(int x, int y, int w, int h, SDL_Renderer* ren, SDL_Color col) {
		xpos = x;
		ypos = y;
		h1 = h;
		w1 = w;
		renderer = ren;
		color = col;
	}

	//Metodo que Actualiza el cuadro de texto
	//@param texto
	void Update(const char* s)
	{
		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = w1;
		destRect.h = h1;
		TTF_Font* Chalk = TTF_OpenFont("./Assets/ChalkDash-O2j4.ttf", 64);
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Chalk, s, color);
		Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	}

	//Metodo que Renderiza el cuadro de texto
	virtual void Render() {
		SDL_RenderCopy(renderer, Message, NULL, &destRect);
	}
};