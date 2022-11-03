#include "Player.h"

void Player::setMovement(float movement) {
	m_movement = movement;
	//printf("%lf\n", m_movement);
}

void Player::update(float dt) {
	sf::Vector2f currentPosition(m_sprite.getPosition());
	m_sprite.setPosition(currentPosition.x + (m_movement * dt), currentPosition.y);
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