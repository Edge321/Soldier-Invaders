/*********************************************************************
 * @file   Soldier.h
 * @brief  The main enemy in this game
 * 
 * @author Edge321
 * @date   December 2022
 *********************************************************************/

#include "Character.h"

#pragma once
class Soldier : public Character
{
public:
	void update(float dt);
	void setSpeed(float speed);
	void changeDirection();
	void moveDown();
	void changeSpeed(float movementModification);
	bool checkOutOfBound();

private:
	float m_movementSpeed = 0;
};

