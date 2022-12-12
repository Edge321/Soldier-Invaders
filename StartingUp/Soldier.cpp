#include "Soldier.h"

bool checkOutOfBound(sf::Sprite sprite);

void Soldier::update(float dt) {
	m_sprite.move(m_movementSpeed * dt, 0);

	if (checkOutOfBound(m_sprite)) {
		m_movementSpeed *= -1;
	}
}
/**
 * @brief Sets the speed of the soldier
 */
void Soldier::setSpeed(float speed) {
	m_movementSpeed = speed;
}
/**
 * @brief Checks if the sprite is out of bounds of the window resolution
 * 
 * @param sprite Sprite to be checked
 * @return true or false
 */
bool checkOutOfBound(sf::Sprite sprite) {
	sf::Vector2i windowSize(1024, 768);

	float spriteSize = sprite.getTexture()->getSize().x;
	if (sprite.getPosition().x > (windowSize.x - spriteSize) || sprite.getPosition().x < 0 + spriteSize)
		return true;

	return false;
}