#pragma once

#include <random>
#include <time.h>

#include "BaseObject.h"
#include "Bomb.h"


class CAlien :
	public CBaseObject
{
private:
	IDiceInvaders *m_system;

	float m_healthPoints;

public:
	explicit CAlien(IDiceInvaders *system);
	~CAlien();

public:
	void onMove(void);
	void onMoveDown(void);

	CBomb* onAttack(void);
	void onHit(CBaseObject *object);
};

