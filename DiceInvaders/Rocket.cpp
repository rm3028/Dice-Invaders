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
