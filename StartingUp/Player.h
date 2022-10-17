#include "Character.h"

class Player : public Character {
public:
	void setMovement(float movement);
	void update(float dt);
	void disabled();
	void enabled();
private:
	float m_movement = 0;
};