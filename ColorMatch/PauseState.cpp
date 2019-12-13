#include "PauseState.h"
#include "GameState.h"
#include "Game.h"
#include "SDL.h"

//Maneja los eventos
void PauseState::HandleEvents() {
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
			game->ChangeState(state);
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

//Maneja las actualizacione
void PauseState::Update()
{
	objBackground->Update();
	std::string tex = "Score: " + std::to_string(score);
	const char* texto = tex.c_str();
	Score->Update(texto);
}

//Maneja las imagenes a renderizar
void PauseState::Render()
{
	SDL_RenderClear(renderer);
	objBackground->Render();
	Score->Render();
	SDL_RenderPresent(renderer);
}
