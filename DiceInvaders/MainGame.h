/*
 * MainGame.h: Define the game object.
 *
 * Authors: Wei-Yun Huang
 * Date: January 09, 2017
 *
 * Copyright © 2017 Wei-Yun Huang.
 * All rights reserved.
 */

#pragma once

#include <windows.h>
#include <cassert>
#include <cstdio>
#include <list>
#include <string>

#include "DiceInvaders.h"
#include "PlayerShip.h"
#include "Rocket.h"
#include "Alien.h"
#include "Bomb.h"


class CMainGame
{
private:
	enum GAMESTATE { GS_LOAD, GS_PLAY, GS_GAMEOVER, GS_NUM };

private:
	GAMESTATE m_gameState;

	IDiceInvaders *m_system;
	HMODULE m_lib;

	int m_winWidth, m_winHeight;
	float m_playTime, m_startTime;

private:
	CPlayerShip *m_playerShip;
	std::list<CRocket*> m_rocketList;

	std::list<CAlien*> m_alienList;
	std::list<CBomb*> m_bombList;

public:
	explicit CMainGame(const wchar_t* libraryPath);
	~CMainGame();

public:
	void initialize(int width, int height);

	void onRocketHitAlien(void);
	void onBombHitPlayerShip();
	void onAlienHitPlayerShip();

private:
	void gameLoad(int rows, int cols);
	void gamePlay(void);
	void gameOver(void);

public:
	void gameLoop(void);
};

