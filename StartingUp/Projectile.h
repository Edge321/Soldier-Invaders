#include "Character.h"
#pragma once
class Projectile : public Character
{
public:
	Projectile();
	~Projectile();

	void update(float dt);
	void rotate(float angleChange);
	void setProjectileSpeed(float projectileSpeed);
	void disabled();
	void enabled();

	bool getOutofBounds() {
		return m_outOfBounds;
	}

	/**
	* @brief Is projectile currently moving in the window?
	*/
	bool getStatus() {
		return m_status;
	}

private:
	float m_projectileSpeed = 100.0f;
	bool m_outOfBounds = false;
	bool m_status = true; 
};

