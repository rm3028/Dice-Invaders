/*
 * DiceInvaders.cpp: The entry point of the program. 
 *
 * Authors: Wei-Yun Huang
 * Date: January 09, 2017
 *
 * Copyright © 2017 Wei-Yun Huang.
 * All rights reserved.
 */

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

