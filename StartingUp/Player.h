#include "Character.h"

class Player : public Character {
public:
	void setMovement(float movement);
	void update(float dt);
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