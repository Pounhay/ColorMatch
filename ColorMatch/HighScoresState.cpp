#include "HighScoresState.h"
#include "StartState.h"
#include "Game.h"
#include "SDL.h"

//Maneja los eventos
void HighScoresState::HandleEvents() {
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
			game->ChangeState(new StartState(renderer, game));
			break;
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
void HighScoresState::Update()
{
	objBackground->Update();
	for (int i = 0; i < 5; i++) {
		if(scoresList.get_at(i)!= NULL)
			tex = std::to_string(i+1) + ". " + std::to_string(scoresList.get_at(i)->value);
		else
			tex = std::to_string(i+1) + ". ----";
		const char* texto = tex.c_str();
		Score[i].Update(texto);;
	}
}

//Maneja el renderizado de las imagenes
void HighScoresState::Render()
{
	SDL_RenderClear(renderer);
	objBackground->Render();
	for (int i = 0; i < 5; i++)
		Score[i].Render();
	SDL_RenderPresent(renderer);
}
