#pragma once
#include "State.h"
#include "SDL.h"
class PauseState : public State
{
public:
	void HandleEvents();
	void Update();
	void Render();
	PauseState(SDL_Renderer* ren, Game* gm, int sc, State* st) : State(ren, gm) {
		score = sc;
		Score = new Text(150, 318, 300, 64, renderer, white);
		objBackground = new GameObject("./Assets/Menu.png", 0, 0, 600, 700, renderer);
		state = st;
	}

private:
	State* state;
	int score;
	Text* Score;
	GameObject* objBackground;
	SDL_Color white = { 255, 255, 255 };
};

