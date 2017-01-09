/*
 * Rocket.h: Define the rocket object.
 *
 * Authors: Wei-Yun Huang
 * Date: January 09, 2017
 *
 * Copyright © 2017 Wei-Yun Huang.
 * All rights reserved.
 */

#pragma once

#include "BaseObject.h"


class CRocket :
	public CBaseObject
{
public:
	explicit CRocket(IDiceInvaders *system);
	~CRocket();

public:
	void update(void);
};

