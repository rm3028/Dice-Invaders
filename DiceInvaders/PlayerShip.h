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

