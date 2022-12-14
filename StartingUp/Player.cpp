#include "Player.h"

void limitArea(sf::Sprite *sprite);

void Player::update(float dt) {
	sf::Vector2f currentPosition(m_sprite.getPosition());
	m_sprite.setPosition(currentPosition.x + (m_movement * dt), currentPosition.y);

	limitArea(&m_sprite);
}
/**
 * @brief Sets the movement for where the player will go. Default is moving to the right
 * 
 * @param movement Movement in x-direction
 */
void Player::setMovement(float movement) {
	m_movement = movement;
	//printf("%lf\n", m_movement);
}
/**
* @brief Makes player in disabled state
*/
void Player::disabled() {
	sf::Color disabledColor = sf::Color(150, 150, 150, 255);
	m_sprite.setColor(disabledColor);
}
/**
* @brief Makes player in enabled state
*/
void Player::enabled() {
	sf::Color enabledColor = sf::Color(255, 255, 255, 255);
	m_sprite.setColor(enabledColor);
}
/**
 * @brief Limits player's movement in the x direction
 * 
 * @param sprite Player's sprite
 */
void limitArea(sf::Sprite *sprite) {
	sf::Vector2i windowSize(1024, 768);

	if (sprite->getPosition().x < sprite->getTexture()->getSize().x)
		sprite->setPosition(sprite->getTexture()->getSize().x, sprite->getPosition().y);
	else if (sprite->getPosition().x > windowSize.x - sprite->getTexture()->getSize().x)
		sprite->setPosition(windowSize.x - sprite->getTexture()->getSize().x, sprite->getPosition().y);
}
