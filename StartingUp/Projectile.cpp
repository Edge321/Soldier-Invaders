#include "Projectile.h"

bool checkOutOfBounds(sf::Sprite sprite);

Projectile::Projectile() {}
Projectile::~Projectile() {}

void Projectile::update(float dt) {
	if (currentType == NORMAL) {
		sf::Vector2f currentPosition(m_sprite.getPosition());
		m_sprite.setPosition(currentPosition.x, currentPosition.y - (m_normalSpeed * dt));
	}
	else if (currentType == GUIDED) {
		const float pi = 3.14159265f;

		m_sprite.rotate(m_angleChange * dt);

		//Converting degrees to radians here
		float x = cos(m_sprite.getRotation() * pi / 180.0f);
		float y = sin(m_sprite.getRotation() * pi / 180.0f);
		//Moves sprite based on rotation
		m_sprite.move(x * m_guidedSpeed * dt, y * m_guidedSpeed * dt);
		//printf("x:%lf\ty:%lf\n", m_sprite.getPosition().x, m_sprite.getPosition().y);
	}

	m_outOfBounds = checkOutOfBounds(m_sprite);
}
/**
 * @brief Rotates the projectile
 */
void Projectile::setRotater(float angleChange) {
	m_angleChange = angleChange;
}
/**
 * @brief Sets how fast the guided projectile moves
 */
void Projectile::setGuidedSpeed(float projectileSpeed) {
	m_guidedSpeed = projectileSpeed;
}
/**
 * @brief Sets how fast the normal projectile moves
 * 
 * @param projectileSpeed
 */
void Projectile::setNormalSpeed(float projectileSpeed) {
	m_normalSpeed = projectileSpeed;
}
/**
 * @brief Sets position of the projectile
 */
void Projectile::setPosition(sf::Vector2f position) {
	m_sprite.setPosition(position);
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
 * @brief Switches the type of rocket to use
 */
void Projectile::switchModes() {
	int temp = ((int) currentType + 1) % 2;
	currentType = (projectileType) temp;
	//printf("temp: %d\n", temp);
	printf("Mode is now: %s\n", temp == 1 ? "Guided" : "Normal");
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