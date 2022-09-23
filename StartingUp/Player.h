#include "Character.h"

class Player : public Character {
public:
	void setMovement(float movement);
	void update(float dt);
private:
	float m_movement = 0;
};