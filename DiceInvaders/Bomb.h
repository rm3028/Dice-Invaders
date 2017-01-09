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

