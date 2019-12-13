#pragma once
#include "State.h"
#include "SDL.h"
#include <iostream>
#include <fstream>

class HighScoresState : public State
{
public:
	void HandleEvents();
	void Update();
	void Render();

	//Inicializa el estado
	//@param renderer donde se va a poner las imagenes
	//@param juego
	//@param score del juego
	HighScoresState(SDL_Renderer* ren, Game* gm) : State(ren, gm) {
		size_t sz = 0;
		std::ifstream myFile("data.bin", std::ios::out | std::ios::binary); 
		myFile.read((char*)(&sz), sizeof(sz));
		for (size_t i = 0; i < sz; ++i)
		{
			int temp;
			myFile.read((char*)(&temp), sizeof(temp));
			scoresList.push_back(temp);
		}
		myFile.close();
		for (int i = 0; i < 5; i++) {
			Text* tx = new Text(150, 78 + (i * 120), 300, 64, renderer, white);
			Score[i] = *tx;
		}
		scoresList.insertion();
		objBackground = new GameObject("./Assets/Menu.png", 0, 0, 600, 700, renderer);
	}

private:
	Text* Score = new Text[5], * Over;
	GameObject* objBackground;
	std::string tex;
	List<int> scoresList;
	SDL_Color white = { 255, 255, 255 };
};



