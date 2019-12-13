#include "Game.h"
#include "GameState.h"
#include "StartState.h"

//Constructor del Game
Game::Game()
{}

//Deconstructor del Game
Game::~Game()
{}

//Inicializador
//@param titulo del juego
//@param ancho de la ventana
//@param alto de la ventana
//@param si el juego esta en fullscreen
void Game::Init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		isRunning = true;
	}
	if (TTF_Init() == 0)
		isRunning = true;
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		isRunning = true;
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		isRunning = true; 

	currentState = new StartState(renderer, this);
}

//Maneja los eventos
void Game::HandleEvents()
{
	currentState->HandleEvents();
}

//Maneja las actualizaciones
void Game::Update()
{
	if (nextState != NULL)
	{
		currentState = nextState;

		nextState = NULL;
	}
	currentState->Update();
}

//Maneja las imagenes a renderizar
void Game::Render()
{
	currentState->Render();
}

//Limpia los recursos
void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

//Cambia de estado
//@param estado al cual cambia
void Game::ChangeState(State* state)
{
	nextState = state;
}