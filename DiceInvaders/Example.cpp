#include "MainGame.h"


int APIENTRY WinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	LPSTR commandLine,
	int commandShow)
{
	CMainGame game(L"DiceInvaders.dll");
	game.initialize(640, 480);
	game.gameLoop();

	return 0;
}

