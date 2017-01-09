/*
 * Alien.cpp: Implement the alien object.
 *
 * Authors: Wei-Yun Huang
 * Date: January 09, 2017
 *
 * Copyright © 2017 Wei-Yun Huang.
 * All rights reserved.
 */

#include "Alien.h"


CAlien::CAlien(IDiceInvaders *system)
	: m_system(system), m_healthPoints(1.f)
{
	m_sprite = rand() % 2 ? m_system->createSprite("data/enemy1.bmp") : \
							m_system->createSprite("data/enemy2.bmp");

	this->setSize(32, 32);
	this->setAttackDamage(1.0);
}


CAlien::~CAlien()
{
}


void CAlien::onMove(void)
{
	this->setPosition(m_position.x + m_speed.x, m_position.y);
}


void CAlien::onMoveDown(void)
{
	this->setPosition(m_position.x, m_position.y + m_speed.y);
}


CBomb* CAlien::onAttack(void)
{
	if (rand() % 1000 == 0 && rand() % 1000 == 0)
	{
		CBomb *bomb = new CBomb(m_system);
		bomb->setPosition(m_position.x, m_position.y + 32);

		return bomb;
	}
	else
	{
		return nullptr;
	}
}


void CAlien::onHit(CBaseObject *object)
{
	this->setHealthPoints(m_healthPoints - object->getAttackDamage());
}
