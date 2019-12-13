#pragma once

#include "GameObject.h"

class Tile : public GameObject
{
	int xpos, ypos;
	int yconst, xconst;
	int h1 = 64;
	int w1 = 64;
	int type;
	bool chosen = false;
	bool falling = false;
	bool swapping = false;
	int sxpos, sypos, speed;
	bool complete = true;

	SDL_Texture* objTexture;
	SDL_Texture* objArrows;
	SDL_Texture* objSwapping;
	SDL_Rect scrRect, destRect;
	SDL_Renderer* renderer;

public:
	int order;
	Tile();
	~Tile();

	//Inicializa el Tile
	//@param renderer donde van a estar las imagens
	//@param posicion inicial en x
	//@param posicion inicial en y
	//@param tipo de Tile
	Tile(SDL_Renderer* ren, int x, int y, int t) {
		renderer = ren;

		objArrows = TextureManager::LoadTexture("./Assets/Arrows.png", renderer);
		xconst = xpos = x;
		yconst = ypos = y;
		SetType(t);
	}

	int GetX() { return xpos; }
	int GetY() { return ypos; }
	int GetType() { return type; }
	int GetH() { return h1; }
	int GetW() { return w1; }
	void Choose() { chosen = true; }
	void UnChoose() { chosen = false; }
	bool GetChoosen() { return chosen; }
	bool GetFalling() { return falling; }
	
	//Maneja las actualizaciones
	virtual void Update()
	{
		scrRect.w = w1;
		scrRect.h = h1;
		scrRect.x = 0;
		scrRect.y = 0;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = scrRect.w;
		destRect.h = scrRect.h;

		if (swapping)
			SwapAnimation();
		if (falling)
			FallAnimation();
	}

	//Hace la animacion de que se estan cambiando las Tiles
	void SwapAnimation() {
		if (xpos > sxpos)
			xpos -= speed;
		if (xpos < sxpos)
			xpos += speed;
		if (ypos > sypos)
			ypos -= speed;
		if (ypos < sypos)
			ypos += speed;
		if (ypos == sypos && xpos == sxpos) {
			swapping = false;
			xpos = xconst;
			ypos = yconst;
		}
	}

	//Hace la animacion de que estan cayendo las Tiles
	void FallAnimation() {
		if (ypos > sypos) {
			ypos -= speed;
		}
		if (ypos < sypos) {
			ypos += speed;
		}
		if (ypos == sypos) {
			falling = false;
			ypos = yconst;
			complete = true;
		}
	}

	//Cambia de posicion un Tile
	//@param posicion inicial en x
	//@param posicion inicial en y
	//@param tipo de Tile
	//@param velocidad del cambio
	void Swap(int x, int y, int t, int s) { swapping = true; sxpos = x; sypos = y; speed = s; objSwapping = objTexture; SetType(t); }

	//Hace caer un Tile
	//@param posicion inicial en y
	//@param tipo de Tile
	//@param velocidad del cambio
	void Fall(int y, int t, int s) { falling = true; complete = false; sypos = y; speed = s; objSwapping = objTexture; SetType(t); }

	//Fija la textura a partir del tipo de Tile
	//@param tipo de Tile
	void SetType(int t) {
		type = t;
		switch (type) {
		case 0:
			objTexture = TextureManager::LoadTexture("./Assets/Tile_0.png", renderer);
			break;
		case 1:
			objTexture = TextureManager::LoadTexture("./Assets/Tile_1.png", renderer);
			break;
		case 2:
			objTexture = TextureManager::LoadTexture("./Assets/Tile_2.png", renderer);
			break;
		case 3:
			objTexture = TextureManager::LoadTexture("./Assets/Tile_3.png", renderer);
			break;
		case 4:
			objTexture = TextureManager::LoadTexture("./Assets/Tile_4.png", renderer);
			break;
		case 5:
			objTexture = TextureManager::LoadTexture("./Assets/Tile_5.png", renderer);
			break;
		case 6:
			objTexture = TextureManager::LoadTexture("./Assets/Tile_6.png", renderer);
			break;
		case 7:
			objTexture = TextureManager::LoadTexture("./Assets/Tile.gif0", renderer);
			break;
		case 8:
			objTexture = TextureManager::LoadTexture("./Assets/Black.png", renderer);
			break;
		case 9:
			objTexture = TextureManager::LoadTexture("./Assets/White.png", renderer);
			break;
		}
	}

	//Renderiza las imagenes
	virtual void Render() {
		if (swapping || falling)
			SDL_RenderCopy(renderer, objSwapping, &scrRect, &destRect);
		else 
			SDL_RenderCopy(renderer, objTexture, &scrRect, &destRect);
		if (chosen)
			SDL_RenderCopy(renderer, objArrows, &scrRect, &destRect);
	}
};