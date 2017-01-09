/*
 * PlayerShip.cpp: Implement the player ship object.
 *
 * Authors: Wei-Yun Huang
 * Date: January 09, 2017
 *
 * Copyright © 2017 Wei-Yun Huang.
 * All rights reserved.
 */

#include "PlayerShip.h"


CPlayerShip::CPlayerShip(IDiceInvaders *system)
	: m_system(system), m_attackSpeed(0.25f)
{
	m_sprite = m_system->createSprite("data/player.bmp");
	this->setSize(32, 16);
	this->setAttackDamage(1.f);
	this->setHealthPoints(3.f);
}


CPlayerShip::~CPlayerShip()
{
}


void CPlayerShip::setAttackSpeed(float speed)
{
	m_attackSpeed = speed;
}


CRocket* CPlayerShip::onKeyboard(IDiceInvaders::KeyStatus &keys)
{
	if (keys.right)
	{
		this->setPosition(this->m_position.x + m_speed.x, this->m_position.y);
	}
	if (keys.left)
	{
		this->setPosition(this->m_position.x - m_speed.x, this->m_position.y);
	}
	if (keys.fire)
	{
		static float lastAttackTime = -FLT_MAX;
		float currentTime = m_system->getElapsedTime();

		if (currentTime - lastAttackTime >= m_attackSpeed)
		{
			CRocket *rocket = new CRocket(m_system);
			rocket->setPosition(m_position.x, m_position.y - 32);

			lastAttackTime = currentTime;

			return rocket;
		}
	}

	return nullptr;
}


void CPlayerShip::onHit(CBaseObject *object)
{
	m_healthPoints -= object->getAttackDamage();
}
