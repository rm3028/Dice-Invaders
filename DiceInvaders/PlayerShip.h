/*
 * PlayerShip.h: Define the player ship object.
 *
 * Authors: Wei-Yun Huang
 * Date: January 09, 2017
 *
 * Copyright © 2017 Wei-Yun Huang.
 * All rights reserved.
 */

#pragma once

#include "BaseObject.h"
#include "Rocket.h"


class CPlayerShip :
	public CBaseObject
{
private:
	IDiceInvaders *m_system;
	float m_attackSpeed;

public:
	explicit CPlayerShip(IDiceInvaders *system);
	~CPlayerShip();

public:
	void setAttackSpeed(float speed);

public:
	CRocket* onKeyboard(IDiceInvaders::KeyStatus &keys);
	void onHit(CBaseObject *object);
};

