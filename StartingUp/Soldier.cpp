#include "Soldier.h"

void Soldier::update(float dt) {
	m_sprite.move(m_movementSpeed * dt, 0);
}
/**
 * @brief Sets the speed of the soldier
 */
void Soldier::setSpeed(float speed) {
	m_movementSpeed = speed;
}
/**
 * @brief Changes the soldier's direction on the x-axis
 */
void Soldier::changeDirection() {
	m_movementSpeed *= -1;
}
/**
 * @brief Moves the sprite down the screen
 */
void Soldier::moveDown() {
	sf::Vector2f offset(0, this->getSize().y);
	m_sprite.move(offset);
}
/**
 * @brief Modifies the soldier's speed
 * 
 * @param speedModification
 */
void Soldier::changeSpeed(float speedModification) {
	//If-else statment checks if speed is a negative number
	if (m_movementSpeed < 0)
		m_movementSpeed -= speedModification;
	else
		m_movementSpeed += speedModification;
}
/**
 * @brief Checks if the sprite is out of bounds of the window resolution
 * 
 * @param sprite Sprite to be checked
 * @return true or false
 */
bool Soldier::checkOutOfBound() {
	sf::Vector2i windowSize(1024, 768);

	float spriteSize = m_sprite.getTexture()->getSize().x;
	if (m_sprite.getPosition().x > (windowSize.x - spriteSize) || m_sprite.getPosition().x < 0 + spriteSize)
		return true;

	return false;
}