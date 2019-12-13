#pragma once

#include "SDL.h"
#include "State.h"
#include "Timer.h"

class GameState : public State
{
public:
	void HandleEvents();
	void Update();
	void Render();
	int CountDown();
	GameState(SDL_Renderer* ren, Game* gm) : State(ren, gm) {
		Time = new Text(456, 99, 100, 32, renderer, white);
		gameBoard = new Board(renderer);
		music = Mix_LoadMUS("./Assets/Ukulele.mp3");
		Mix_PlayMusic(music, 1);
	}

private:
	bool init = false;
	Text* Time;
	Board* gameBoard;	 
	Timer timer;
	SDL_Color white = { 255, 255, 255 }; 
	Mix_Music* music;
};

