/*
 * Rocket.cpp: Implement the rocket object.
 *
 * Authors: Wei-Yun Huang
 * Date: January 09, 2017
 *
 * Copyright © 2017 Wei-Yun Huang.
 * All rights reserved.
 */

#include "Rocket.h"


CRocket::CRocket(IDiceInvaders *system)
{
	m_sprite = system->createSprite("data/rocket.bmp");
	this->setSize(8, 16);
	this->setAttackDamage(1.0);
}


CRocket::~CRocket()
{
}


void CRocket::update(void)
{
	this->setPosition(this->m_position.x, this->m_position.y - m_speed.y);
}
