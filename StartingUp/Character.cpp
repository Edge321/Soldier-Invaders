#include "Character.h"

Character::Character() {}
Character::~Character() {}
/**
 * @brief Initializes an object and its sprites
 * 
 * @param texturePath File path of the texture image
 * @param position Location of the character (World space)
 */
void Character::init(std::string texturePath, sf::Vector2f position) {
	m_position = position;

	m_texture.loadFromFile(texturePath.c_str());

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
}
/**
 * @brief Changes the rotation of the character
 * 
 * @param rotation
 */
void Character::changeRotation(float rotation) {
	m_sprite.setRotation(rotation);
}
/**
 * @brief Sets the scale of the sprite. (1.0f, 1.0f) is the default
 */
void Character::setScale(sf::Vector2f scale) {
	m_sprite.setScale(scale);
}
/**
 * @brief Gets the sprite of the character
 * 
 * @return sf::Sprite
 */
sf::Sprite Character::getSprite() {
	return m_sprite;
}
/**
 * @brief Returns the size of the sprite according to its scale
 * 
 * @return Vector2f size
 */
sf::Vector2f Character::getSize() {
	sf::Vector2f spriteScale = m_sprite.getScale();
	sf::Vector2u spriteSize = m_sprite.getTexture()->getSize();

	return sf::Vector2f(spriteSize.x * spriteScale.x, spriteSize.y * spriteScale.y);
}
