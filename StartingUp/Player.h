/*********************************************************************
 * @file   Player.h
 * @brief  What the player will be controlling
 * 
 * @author Edge321
 * @date   December 2022
 *********************************************************************/

#include "Character.h"

class Player : public Character {
public:
	void update(float dt);
	void setMovement(float movement);
	void disabled();
	void enabled();

	void setHeroMove(bool heroMove) {
		m_canHeroMove = heroMove;
	}
	
	bool getHeroMove() {
		return m_canHeroMove;
	}

private:
	float m_movement = 0;
	bool m_canHeroMove = true;
};