#include "GameOverState.h"
#include "StartState.h"
#include "HighScoresState.h"
#include "Game.h"
#include "SDL.h"

//Maneja los eventos
void GameOverState::HandleEvents() {
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
			Save();
			game->ChangeState(new HighScoresState(renderer, game));
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
void GameOverState::Update()
{
	objBackground->Update();
	std::string tex = "Score: " + std::to_string(score);
	const char* texto = tex.c_str();
	Score->Update(texto);
	Over->Update("Game Over");
}

//Maneja el renderizado de las imagenes
void GameOverState::Render()
{
	SDL_RenderClear(renderer);
	objBackground->Render();
	Score->Render();
	Over->Render();
	SDL_RenderPresent(renderer);
}

//Guarda los High Scores
void GameOverState::Save()
{
	size_t sz = scoresList.size;
	std::ofstream myFile("data.bin", std::ios::out | std::ios::binary);
	myFile.write((const char*)(&sz), sizeof(sz));

	NodoT<int>* temp = scoresList.first;
	for (int i = 0; i < scoresList.size; i++)
	{
		int temp2 = temp->value;
		myFile.write((const char*)(&temp2), sizeof(temp2));
		temp = temp->next;
	}
	myFile.close();
}
