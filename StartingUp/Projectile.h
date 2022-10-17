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

private:
	float m_projectileSpeed = 100.0f;
};

