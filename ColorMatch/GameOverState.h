#pragma once
#include "State.h"
#include "SDL.h"
#include <iostream>
#include <fstream>

class GameOverState : public State
{
public:
	void HandleEvents();
	void Update();
	void Render();
	void Save();

	//Inicializa el estado
	//@param renderer donde se va a poner las imagenes
	//@param juego
	//@param score del juego
	GameOverState(SDL_Renderer* ren, Game* gm, int sc) : State(ren, gm) {
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
		score = sc;
		Over = new Text(150, 286, 300, 64, renderer, white);
		Score = new Text(150, 350, 300, 64, renderer, white);
		objBackground = new GameObject("./Assets/Menu.png", 0, 0, 600, 700, renderer);
		scoresList.push_back(score);
	}

private:
	int score;
	List<int> scoresList;
	Text* Score,* Over;
	GameObject* objBackground;
	SDL_Color white = { 255, 255, 255 };
};

