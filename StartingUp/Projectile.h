/*********************************************************************
 * @file   Projectile.h
 * @brief  Projectile that the player will be shooting
 * 
 * @author Edge321
 * @date   December 2022
 *********************************************************************/

#include "Character.h"
#pragma once
class Projectile : public Character
{
public:
	Projectile();
	~Projectile();

	void update(float dt);
	void setRotater(float angleChange);
	void setGuidedSpeed(float projectileSpeed);
	void setNormalSpeed(float projectileSpeed);
	void setPosition(sf::Vector2f position);
	void disabled();
	void enabled();
	void switchModes();

	enum projectileType {
		NORMAL, GUIDED
	};

	bool getOutofBounds() {
		return m_outOfBounds;
	}
	//Is the object currently active in the window?
	bool getStatus() {
		return m_status;
	}
	projectileType getType() {
		return currentType;
	}
	
private:
	float m_guidedSpeed = 100.0f;
	float m_normalSpeed = 200.0f;
	float m_angleChange = 0;
	bool m_outOfBounds = false;
	bool m_status = true; 
	projectileType currentType = NORMAL;
};

