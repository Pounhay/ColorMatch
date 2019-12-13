#pragma once

#include "Board.h"
#include <vector>
#include "State.h"

class State;

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int width, int height, bool fullscreen);

	void HandleEvents();
	void Update();
	bool Running() { return isRunning; }
	void Quit() { isRunning = false; }
	void Render();
	void Clean();
	void ChangeState(State* state); 


private:
	bool isRunning = false;
	bool turn = true;
	bool ascend = true;
	State* currentState;
	State* nextState;
	
	SDL_Window* window;
	SDL_Renderer* renderer;
};
