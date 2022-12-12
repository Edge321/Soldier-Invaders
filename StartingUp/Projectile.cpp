#include "Projectile.h"

bool checkOutOfBounds(sf::Sprite sprite);

Projectile::Projectile() {}
Projectile::~Projectile() {}

void Projectile::update(float dt) {
	const float pi = 3.14159265f;
	sf::Vector2i windowSize(1024, 768);

	//Converting degrees to radians here
	float x = cos(m_sprite.getRotation() * pi / 180.0f);
	float y = sin(m_sprite.getRotation() * pi / 180.0f);
	//Moves sprite based on rotation
	m_sprite.move(x * m_projectileSpeed * dt, y * m_projectileSpeed * dt);

	m_outOfBounds = checkOutOfBounds(m_sprite);

	//printf("x:%lf\ty:%lf\n", m_sprite.getPosition().x, m_sprite.getPosition().y);
}
/**
 * @brief Rotates the projectile
 */
void Projectile::rotate(float angleChange) {
	m_sprite.rotate(angleChange);
}
/**
 * @brief Sets how fast the projectile will move
 */
void Projectile::setProjectileSpeed(float projectileSpeed) {
	m_projectileSpeed = projectileSpeed;
}
/**
 * @brief Disables status of projectile being active
 */
void Projectile::disabled() {
	m_sprite.setColor(sf::Color::Transparent);
	m_status = false;
}
/**
 * @brief Enables status of projectile being active
 */
void Projectile::enabled() {
	m_sprite.setColor(sf::Color::White);
	m_status = true;
}
/**
 * @brief Checks if the sprite is outside the window resolution
 * 
 * @param sprite Sprite in question
 * @return true or false
 */
bool checkOutOfBounds(sf::Sprite sprite) {
	sf::Vector2i windowSize(1024, 768);
	int offScreen = 10;

	if (sprite.getPosition().x > (windowSize.x + offScreen) || sprite.getPosition().x < 0 - offScreen ||
		sprite.getPosition().y > (windowSize.y + offScreen) || sprite.getPosition().y < 0 - offScreen)
		return true;

	return false;
}