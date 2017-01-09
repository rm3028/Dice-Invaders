/*
 * Bomb.cpp: Implement the bomb object.
 *
 * Authors: Wei-Yun Huang
 * Date: January 09, 2017
 *
 * Copyright © 2017 Wei-Yun Huang.
 * All rights reserved.
 */

#include "Bomb.h"


CBomb::CBomb(IDiceInvaders *system)
{
	m_sprite = system->createSprite("data/bomb.bmp");
	this->setSize(8, 16);
	this->setAttackDamage(1.0);
}


CBomb::~CBomb()
{
}


void CBomb::update(void)
{
	this->setPosition(this->m_position.x, this->m_position.y + m_speed.y);
}
