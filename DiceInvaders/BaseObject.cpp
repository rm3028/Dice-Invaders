#include "BaseObject.h"


CBaseObject::CBaseObject()
	: m_sprite(nullptr), m_attackDamage(0.f), m_healthPoints(1.f)
{
	m_position.x = 0.f;
	m_position.y = 0.f;

	m_speed.x = 0.f;
	m_speed.y = 0.f;

	m_minPosition.x = 0.f;
	m_maxPosition.x = FLT_MAX;

	m_minPosition.y = 0.f;
	m_maxPosition.y = FLT_MAX;
}


CBaseObject::~CBaseObject()
{
 	if (m_sprite != nullptr) { m_sprite->destroy(); m_sprite = nullptr; }
}


void CBaseObject::setBoundariesX(float minPosX, float maxPosX)
{
	m_minPosition.x = minPosX;
	m_maxPosition.x = maxPosX;

	m_position.x = m_position.x > m_maxPosition.x ? m_maxPosition.x : m_position.x;
	m_position.x = m_position.x < m_minPosition.x ? m_minPosition.x : m_position.x;
}


void CBaseObject::setBoundariesY(float minPosY, float maxPosY)
{
	m_minPosition.y = minPosY;
	m_maxPosition.y = maxPosY;

	m_position.y = m_position.y > m_maxPosition.y ? m_maxPosition.y : m_position.y;
	m_position.y = m_position.y < m_minPosition.y ? m_minPosition.y : m_position.y;
}


void CBaseObject::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;

	m_position.x = m_position.x > m_maxPosition.x ? m_maxPosition.x : m_position.x;
	m_position.x = m_position.x < m_minPosition.x ? m_minPosition.x : m_position.x;
	m_position.y = m_position.y > m_maxPosition.y ? m_maxPosition.y : m_position.y;
	m_position.y = m_position.y < m_minPosition.y ? m_minPosition.y : m_position.y;

	m_boundingRect.x = m_position.x - (m_boundingRect.width / 2.f);
	m_boundingRect.y = m_position.y - (m_boundingRect.height / 2.f);
}


void CBaseObject::setSpeedX(float speedX)
{
	m_speed.x = speedX;
}


void CBaseObject::setSpeedY(float speedY)
{
	m_speed.y = speedY;
}


void CBaseObject::setSpeed(Vector2D speed)
{
	m_speed = speed;
}


void CBaseObject::setSize(float width, float height)
{
	m_boundingRect.x = m_position.x - (width / 2.f);
	m_boundingRect.y = m_position.y - (height / 2.f);
	m_boundingRect.width = width;
	m_boundingRect.height = height;
}


void CBaseObject::setAttackDamage(float attackDamage)
{
	m_attackDamage = attackDamage;
}


void CBaseObject::setHealthPoints(float healthPoints)
{
	m_healthPoints = healthPoints > 0.f ? healthPoints : 0.f;
}


void CBaseObject::draw(void)
{
	m_sprite->draw((int)m_position.x, (int)m_position.y);
}
