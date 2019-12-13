#include "TextureManager.h"

//Carga una textura
//@param lugar de la textura
//@param renderer donde se ponen las imagenes
SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* ren)
{
	SDL_Surface* tempSurface = IMG_Load(texture); 
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}