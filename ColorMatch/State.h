#pragma once
#include "Game.h"
class Game;
class State
{
public:

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	void ChangeState( State* state) {
		ChangeState(state);
	}
protected:
	Game* game;
	SDL_Renderer* renderer;
	State(SDL_Renderer* ren, Game* gm) { renderer = ren; game = gm; }
};

