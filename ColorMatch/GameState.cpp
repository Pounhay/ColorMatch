#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "Game.h"
#include "SDL.h"

//Maneja los eventos
void GameState::HandleEvents() {
	int mx, my;
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		game->Quit();
		break;
		game->Quit();
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			if (init == false) {
				gameBoard->Init();
				timer.start();
				init = true;
			}
			SDL_GetMouseState(&mx, &my);
			if (!gameBoard->GetActive())
				gameBoard->TileSelect(mx, my);
			else
				gameBoard->TileMove(mx, my);;
			break;
		case SDL_BUTTON_RIGHT:
			timer.stop();
			Mix_PauseMusic();
			game->ChangeState(new PauseState(renderer, game, gameBoard->GetScore(), this));
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
void GameState::Update()
{
	if (!Mix_PausedMusic())
		Mix_ResumeMusic();
	timer.unpause();
	gameBoard->Update();
	Time->Update(std::to_string(CountDown()).c_str());
	if (CountDown() == 0){
		Mix_PauseMusic();
		game->ChangeState(new GameOverState(renderer, game, gameBoard->GetScore()));
	}
}

//Maneja las imagenes a renderizar
void GameState::Render()
{
	SDL_RenderClear(renderer);
	gameBoard->Render();
	Time->Render();
	SDL_RenderPresent(renderer);
}

//Contador
int GameState::CountDown()
{
	return 30 - timer.getTicks();
}

