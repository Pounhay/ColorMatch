#include "StartState.h"
#include "GameState.h"
#include "HighScoresState.h"
#include "Game.h"
#include "SDL.h"

//Maneja los eventos
void StartState::HandleEvents() {
	int mx, my;
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		game->Quit();
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			IsClicked();
		case SDL_BUTTON_RIGHT:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

//Maneja las actualizaciones
void StartState::Update()
{
	objBackground->Update();
	IsOver();
	Start->Update("Start");
	HighScores->Update("High Scores");
	Exit->Update("Exit");
}

//Maneja las imagenes a renderizar
void StartState::Render()
{
	SDL_RenderClear(renderer);
	objBackground->Render();
	Start->Render();
	HighScores->Render();
	Exit->Render();
	SDL_RenderPresent(renderer);
}

//Colorea los textos si pasan por ellos
void StartState::IsOver() {
	int mx1, my1;
	SDL_GetMouseState(&mx1, &my1);
	if ((mx1 > Start->xpos) && (mx1 < Start->xpos + Start->w1) && (my1 > Start->ypos) && (my1 < Start->ypos + Start->h1))
		Start->color = blue;
	else if ((mx1 > HighScores->xpos) && (mx1 < HighScores->xpos + HighScores->w1) && (my1 > HighScores->ypos) && (my1 < HighScores->ypos + HighScores->h1))
		HighScores->color = blue;
	else if ((mx1 > Exit->xpos) && (mx1 < Exit->xpos + Exit->w1) && (my1 > Exit->ypos) && (my1 < Exit->ypos + Exit->h1))
		Exit->color = blue;
	else {
		Exit->color = white;
		Start->color = white;
		HighScores->color = white;
	}
}

//Cambia de estados dependiendo del text
void StartState::IsClicked() {
	int mx1, my1;
	SDL_GetMouseState(&mx1, &my1);
	if ((mx1 > Start->xpos) && (mx1 < Start->xpos + Start->w1) && (my1 > Start->ypos) && (my1 < Start->ypos + Start->h1))
		game->ChangeState(new GameState(renderer, game));
	else if ((mx1 > HighScores->xpos) && (mx1 < HighScores->xpos + HighScores->w1) && (my1 > HighScores->ypos) && (my1 < HighScores->ypos + HighScores->h1))
		game->ChangeState(new HighScoresState(renderer, game));
	else if ((mx1 > Exit->xpos) && (mx1 < Exit->xpos + Exit->w1) && (my1 > Exit->ypos) && (my1 < Exit->ypos + Exit->h1))
		game->Quit();
}