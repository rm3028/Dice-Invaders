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

