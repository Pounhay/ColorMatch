#pragma once
#include "SDL.h"
#include "State.h"
#include "Text.h"

class StartState : public State
{
public:

	void HandleEvents();
	void Update();
	void Render();

	void IsOver();
	void IsClicked();

	StartState(SDL_Renderer* ren, Game* gm) : State(ren, gm) {
		Start = new Text(150, 128, 300, 64, renderer, white);
		HighScores = new Text(150, 302, 300, 64, renderer, white);
		Exit = new Text(150, 476, 300, 64, renderer, white);
		objBackground = new GameObject("./Assets/Menu.png", 0, 0, 600, 700, renderer);
	}
private:
	Text* Start;
	Text* HighScores;
	Text* Exit; 
	GameObject* objBackground;
	SDL_Color white = { 255, 255, 255 };
	SDL_Color blue = { 42, 160, 200 };
};

