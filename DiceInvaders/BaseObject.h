#pragma once

#include <float.h>
#include "DiceInvaders.h"


struct Vector2D
{
	float x;
	float y;

	Vector2D() : x(0.f), y(0.f) {}
};


struct BoundingRect
{
	float x;
	float y;
	float width;
	float height;

	BoundingRect() : x(0.f), y(0.f), width(0.f), height(0.f) {}
};


class CBaseObject
{
protected:
	ISprite *m_sprite;

	Vector2D m_position;
	Vector2D m_minPosition, m_maxPosition;

	Vector2D m_speed;

	BoundingRect m_boundingRect;

	float m_attackDamage;
	float m_healthPoints;

public:
	CBaseObject();
	~CBaseObject();

public:
	void setBoundariesX(float minX, float maxX);
	void setBoundariesY(float minY, float maxY);
	void setPosition(float x, float y);

	void setSpeedX(float speedX);
	void setSpeedY(float speedY);
	void setSpeed(Vector2D speed);

	void setSize(float width, float height);

	void setAttackDamage(float attackDamage);
	void setHealthPoints(float healthPoints);

public:
	inline Vector2D getPosition(void) { return m_position; }
	inline Vector2D getSpeed(void) { return m_speed; }
	inline BoundingRect getBoundingRect(void) { return m_boundingRect; }

	inline bool touchBoundaryX(void) { return m_minPosition.x == m_position.x || m_maxPosition.x == m_position.x; }
	inline bool touchBoundaryY(void) { return m_minPosition.y == m_position.y || m_maxPosition.y == m_position.y; }

	inline bool isHitted(float x, float y) {
		return x >= m_boundingRect.x && y >= m_boundingRect.y && \
			   x <= m_boundingRect.x + m_boundingRect.width && y <= m_boundingRect.y + m_boundingRect.height; 
	}

	inline bool isHitted(BoundingRect &boundingRect) {
		return this->isHitted(boundingRect.x, boundingRect.y) || \
			   this->isHitted(boundingRect.x + boundingRect.width, boundingRect.y) || \
			   this->isHitted(boundingRect.x, boundingRect.y + boundingRect.height) || \
			   this->isHitted(boundingRect.x + boundingRect.width, boundingRect.y + boundingRect.height);
	}

	inline float getAttackDamage(void) { return m_attackDamage; }
	inline float getHealthPoints(void) { return m_healthPoints; }

	inline bool isAlive(void) { return m_healthPoints > 0.f; }
	
public:
	void draw(void);
};

