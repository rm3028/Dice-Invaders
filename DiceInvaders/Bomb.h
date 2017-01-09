/*
 * Bomb.h: Define the bomb object.
 *
 * Authors: Wei-Yun Huang
 * Date: January 09, 2017
 *
 * Copyright © 2017 Wei-Yun Huang.
 * All rights reserved.
 */

#pragma once

#include "BaseObject.h"


class CBomb :
	public CBaseObject
{
public:
	explicit CBomb(IDiceInvaders *system);
	~CBomb();

public:
	void update(void);
};

