#pragma once

#include "SDL.h"
#include "State.h"

class Timer 
{
	Uint32 mStartTicks;

	Uint32 mPausedTicks;

	bool mPaused;
	bool mStarted;
public:

	//Inicia el temporizador
	void start()
	{
		mStarted = true;
		mPaused = false;

		mStartTicks = SDL_GetTicks();
		mPausedTicks = 0;
	}

	//Detiene el temporizador
	void stop()
	{
		mStarted = false;
		mPaused = false;

		mStartTicks = 0;
		mPausedTicks = 0;
	}

	//Pausa el temporizador
	void pause()
	{
		if (mStarted && !mPaused)
		{
			mPaused = true;
			mPausedTicks = SDL_GetTicks() - mStartTicks;
			mStartTicks = 0;
		}
	}

	//Hace que el temporizador siga
	void unpause()
	{
		if (mStarted && mPaused)
		{
			mPaused = false;
			mStartTicks = SDL_GetTicks() - mPausedTicks;
			mPausedTicks = 0;
		}
	}

	//Devuelve el tiempo transcurrido en segundos
	Uint32 getTicks()
	{
		Uint32 time = 0;
		if (mStarted)
		{
			if (mPaused)
			{
				time = mPausedTicks;
			}
			else
			{
				time = SDL_GetTicks() - mStartTicks;
			}
		}

		return time / 1000.f;
	}

	//Devuelve si el temporizador ya empezo
	bool isStarted()
	{
		return mStarted;
	}

	//Devuelve si el temporizador esta en pausa
	bool isPaused()
	{
		return mPaused && mStarted;
	}

	//Constructo del temporizado
	Timer() {
		mStartTicks = 0;
		mPausedTicks = 0;

		mPaused = false;
		mStarted = false;
	}
};
