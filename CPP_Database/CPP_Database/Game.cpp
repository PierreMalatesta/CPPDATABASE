#include "Game.h"

Game::Game()
{

}

void Game::Run()
{
	Init();

	while (IsGameRunning())
	{
		Update();
		Draw();
	}

	Shutdown();
}
