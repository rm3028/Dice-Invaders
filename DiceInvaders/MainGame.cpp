/*
 * MainGame.cpp: Implement the game object.
 *
 * Authors: Wei-Yun Huang
 * Date: January 09, 2017
 *
 * Copyright © 2017 Wei-Yun Huang.
 * All rights reserved.
 */

#include "MainGame.h"


CMainGame::CMainGame(const wchar_t* libraryPath)
	: m_gameState(GS_LOAD), m_playerShip(nullptr), m_playTime(0.f), m_startTime(0.f)
{
	srand(time(NULL));

	m_lib = LoadLibraryW(libraryPath);
	assert(m_lib);

	DiceInvadersFactoryType* factory = (DiceInvadersFactoryType*)GetProcAddress(
		m_lib, "DiceInvadersFactory");
	m_system = factory();
	assert(m_system);
}


CMainGame::~CMainGame()
{
	if (m_playerShip != nullptr) { delete m_playerShip; m_playerShip = nullptr; }

	for (std::list <CRocket*>::iterator rocket = m_rocketList.begin(); rocket != m_rocketList.end(); rocket++)
	{
		if (*rocket != nullptr) { delete *rocket; *rocket = nullptr; }
	}
	m_rocketList.clear();

	for (std::list <CAlien*>::iterator alien = m_alienList.begin(); alien != m_alienList.end(); alien++)
	{
		if (*alien != nullptr) { delete *alien; *alien = nullptr; }
	}
	m_alienList.clear();

	for (std::list <CBomb*>::iterator bomb = m_bombList.begin(); bomb != m_bombList.end(); bomb++)
	{
		if (*bomb != nullptr) { delete *bomb; *bomb = nullptr; }
	}
	m_bombList.clear();

	m_system->destroy();
	FreeLibrary(m_lib);
}


void CMainGame::initialize(int width, int height)
{
	// Initialize window size
	m_winWidth = width;
	m_winHeight = height;
	m_system->init(m_winWidth, m_winHeight);

	// Initialize player ship
	m_playerShip = new CPlayerShip(m_system);
	m_playerShip->setBoundariesX(0, m_winWidth - 32);
	m_playerShip->setBoundariesY(m_winHeight - 32, m_winHeight - 32);
	m_playerShip->setPosition(m_winWidth >> 1, 0);
}


void CMainGame::onRocketHitAlien(void)
{
	for (std::list <CRocket*>::iterator rocket = m_rocketList.begin(); rocket != m_rocketList.end(); rocket++)
	{
		for (std::list <CAlien*>::iterator alien = m_alienList.begin(); alien != m_alienList.end(); alien++)
		{
			if (*alien == nullptr)
				continue;
			else
			{
				if ((*alien)->isHitted((*rocket)->getBoundingRect()))
				{
					(*alien)->onHit(*rocket);

					if (!(*alien)->isAlive()) { delete *alien; *alien = nullptr; }
					delete *rocket; *rocket = nullptr;

					break;
				}
			}
		}
	}
	m_rocketList.remove(nullptr);
	m_alienList.remove(nullptr);
}


void CMainGame::onBombHitPlayerShip(void)
{
	for (std::list <CBomb*>::iterator bomb = m_bombList.begin(); bomb != m_bombList.end(); bomb++)
	{
		if (m_playerShip->isHitted((*bomb)->getBoundingRect()))
		{
			m_playerShip->onHit(*bomb);
			delete *bomb; *bomb = nullptr;
		}
	}
	m_bombList.remove(nullptr);
}


void CMainGame::onAlienHitPlayerShip()
{
	for (std::list <CAlien*>::iterator alien = m_alienList.begin(); alien != m_alienList.end(); alien++)
	{
		if (m_playerShip->isHitted((*alien)->getBoundingRect()))
		{
			m_playerShip->onHit(*alien);
			delete *alien; *alien = nullptr;
		}
	}
	m_alienList.remove(nullptr);
}


void CMainGame::gameLoad(int rows, int cols)
{
	// Update time
	static float lastTime = m_system->getElapsedTime();

	m_playTime = m_system->getElapsedTime();
	float move = (m_playTime - lastTime) * 160.0f;
	lastTime = m_playTime;

	// Draw message
	m_system->drawText(0, 0, ("Time: " + std::to_string(m_playTime - m_startTime)).c_str());
	m_system->drawText(m_winWidth >> 1, 0, ("Health: " + std::to_string((int)m_playerShip->getHealthPoints())).c_str());

	if (m_alienList.empty())
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				CAlien *alien = new CAlien(m_system);
				alien->setBoundariesX(0, m_winWidth - 32);
				alien->setBoundariesY(-32 * i, m_winHeight - 32);
				alien->setPosition(j * 32, i * -32);
				alien->setSpeedX(move);
				alien->setSpeedY(32);

				m_alienList.push_back(alien);
			}
		}
	}
	else
	{
		m_gameState = GS_PLAY;

		// Draw alien
		for (std::list <CAlien*>::iterator alien = m_alienList.begin(); alien != m_alienList.end(); alien++)
		{
			Vector2D alienPosition = (*alien)->getPosition();
			alienPosition.y += move;

			(*alien)->setPosition(alienPosition.x, alienPosition.y);
			(*alien)->draw();

			if (alienPosition.y < 0.f) m_gameState = GS_LOAD;
		}

		// Draw player ship
		m_playerShip->draw();

		if (m_gameState == GS_PLAY)
		{
			for (std::list <CAlien*>::iterator alien = m_alienList.begin(); alien != m_alienList.end(); alien++)
			{
				(*alien)->setSpeedX(move);
				(*alien)->onMove();
			}
		}
	}
}


void CMainGame::gamePlay(void)
{
	// Update time
	static float lastTime = m_system->getElapsedTime();

	m_playTime = m_system->getElapsedTime();
	float move = (m_playTime - lastTime) * 160.0f;
	lastTime = m_playTime;

	// Collision detection
	this->onRocketHitAlien();
	this->onBombHitPlayerShip();
	this->onAlienHitPlayerShip();

	// Draw message
	m_system->drawText(0, 0, ("Time: " + std::to_string(m_playTime - m_startTime)).c_str());
	m_system->drawText(m_winWidth >> 1, 0, ("Health: " + std::to_string((int)m_playerShip->getHealthPoints())).c_str());

	if (!m_alienList.empty())
	{
		// Draw alien
		bool alienTouchBoundaryX = false, alienTouchBoundaryY = false;
		for (std::list <CAlien*>::iterator alien = m_alienList.begin(); alien != m_alienList.end(); alien++)
		{
			alienTouchBoundaryX |= (*alien)->touchBoundaryX();
			alienTouchBoundaryY |= (*alien)->touchBoundaryY();
		}
		for (std::list <CAlien*>::iterator alien = m_alienList.begin(); alien != m_alienList.end(); alien++)
		{
			if (alienTouchBoundaryX && move != 0.f)
			{
				(*alien)->setSpeedX(((*alien)->getSpeed().x) > 0.f ? -move : move);
				(*alien)->onMoveDown();
			}
			else if (move != 0.f)
			{
				(*alien)->setSpeedX(((*alien)->getSpeed().x) > 0.f ? move : -move);
			}

			(*alien)->onMove();
			(*alien)->draw();

			CBomb *bomb = (*alien)->onAttack();
			if (bomb != nullptr)
			{
				m_bombList.push_back(bomb);
			}
		}
		m_alienList.remove(nullptr);

		// Draw bomb
		for (std::list <CBomb*>::iterator bomb = m_bombList.begin(); bomb != m_bombList.end(); bomb++)
		{
			if ((*bomb)->touchBoundaryY())
			{
				delete *bomb; *bomb = nullptr;
			}
			else
			{
				(*bomb)->setSpeedY(move);
				(*bomb)->update();
				(*bomb)->draw();
			}
		}
		m_bombList.remove(nullptr);

		// Draw rocket
		for (std::list <CRocket*>::iterator rocket = m_rocketList.begin(); rocket != m_rocketList.end(); rocket++)
		{
			if ((*rocket)->touchBoundaryY())
			{
				delete *rocket; *rocket = nullptr;
			}
			else
			{
				(*rocket)->setSpeedY(move);
				(*rocket)->update();
				(*rocket)->draw();
			}
		}
		m_rocketList.remove(nullptr);

		// Draw player ship
		if (!m_playerShip->isAlive() || alienTouchBoundaryY)
		{
			m_gameState = GS_GAMEOVER; return;
		}
		else
		{
			m_playerShip->setSpeedX(move);
			m_playerShip->draw();
		}

		// Handle keyboard events
		IDiceInvaders::KeyStatus keys;
		m_system->getKeyStatus(keys);

		CRocket *rocket = m_playerShip->onKeyboard(keys);
		if (rocket != nullptr)
		{
			m_rocketList.push_back(rocket);
		}
	}
	else
	{
		for (std::list <CRocket*>::iterator rocket = m_rocketList.begin(); rocket != m_rocketList.end(); rocket++)
		{
			if (*rocket != nullptr) { delete *rocket; *rocket = nullptr; }
		}
		m_rocketList.clear();

		for (std::list <CBomb*>::iterator bomb = m_bombList.begin(); bomb != m_bombList.end(); bomb++)
		{
			if (*bomb != nullptr) { delete *bomb; *bomb = nullptr; }
		}
		m_bombList.clear();

		m_gameState = GS_LOAD;
	}
}


void CMainGame::gameOver(void)
{
	// Draw message
	m_system->drawText(0, 0, ("Time: " + std::to_string(m_playTime - m_startTime)).c_str());
	m_system->drawText(m_winWidth >> 1, 0, ("Health: " + std::to_string((int)m_playerShip->getHealthPoints())).c_str());
	m_system->drawText((m_winWidth >> 1) - 32, (m_winHeight >> 1) - 16, ("Game Over !"));
	m_system->drawText((m_winWidth >> 1) - 80, (m_winHeight >> 1) + 16, ("Press \"SPACE\" To Restart ! "));

	// Draw alien
	for (std::list <CAlien*>::iterator alien = m_alienList.begin(); alien != m_alienList.end(); alien++)
	{
		(*alien)->draw();
	}

	// Draw bomb
	for (std::list <CBomb*>::iterator bomb = m_bombList.begin(); bomb != m_bombList.end(); bomb++)
	{
		(*bomb)->draw();
	}

	// Draw rocket
	for (std::list <CRocket*>::iterator rocket = m_rocketList.begin(); rocket != m_rocketList.end(); rocket++)
	{
		(*rocket)->draw();
	}

	// Draw player ship
	if (m_playerShip->isAlive())
	{
		m_playerShip->draw();
	}

	// Handle keyboard events
	IDiceInvaders::KeyStatus keys;
	m_system->getKeyStatus(keys);

	if (keys.fire)
	{
		// Initialize player ship
		if (m_playerShip != nullptr) { delete m_playerShip; m_playerShip = nullptr; }
		m_playerShip = new CPlayerShip(m_system);
		m_playerShip->setBoundariesX(0, m_winWidth - 32);
		m_playerShip->setBoundariesY(m_winHeight - 32, m_winHeight - 32);
		m_playerShip->setPosition(m_winWidth >> 1, 0);

		for (std::list <CRocket*>::iterator rocket = m_rocketList.begin(); rocket != m_rocketList.end(); rocket++)
		{
			if (*rocket != nullptr) { delete *rocket; *rocket = nullptr; }
		}
		m_rocketList.clear();

		for (std::list <CAlien*>::iterator alien = m_alienList.begin(); alien != m_alienList.end(); alien++)
		{
			if (*alien != nullptr) { delete *alien; *alien = nullptr; }
		}
		m_alienList.clear();

		for (std::list <CBomb*>::iterator bomb = m_bombList.begin(); bomb != m_bombList.end(); bomb++)
		{
			if (*bomb != nullptr) { delete *bomb; *bomb = nullptr; }
		}
		m_bombList.clear();

		m_startTime = m_system->getElapsedTime();
		m_gameState = GS_LOAD;
	}
}


void CMainGame::gameLoop(void)
{
	while (m_system->update())
	{
		switch (m_gameState)
		{
		case CMainGame::GS_LOAD:
			this->gameLoad(3, 10);
			break;
		case CMainGame::GS_PLAY:
			this->gamePlay();
			break;
		case CMainGame::GS_GAMEOVER:
			this->gameOver();
			break;
		default:
			break;
		}
	}
}
