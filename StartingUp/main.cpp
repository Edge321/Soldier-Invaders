#include "Background.h"
#include "Character.h"
#include "Player.h"
#include "Projectile.h"
#include "Soldier.h"
#include "Bindings.h"
#include "Barrier.h"
#include <iostream>

/*
The game to make: can guide your missile, space invaders-like

Ideas:
Make the rocket have a limited time active
Player can explode rocket before the limited time so they can move again
Player is able to kill themselves with their rocket
*/

void movement(float xDirection);
void shoot();
bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2);

Bindings binds;
/* Window parameters */
sf::Vector2i windowSize(1024, 768);
sf::VideoMode vm(windowSize.x, windowSize.y);
sf::RenderWindow window(vm, "Soldier Invaders", sf::Style::Default);
int frameLimit = 60;

Background bg;
Background sky;
/* Player parameters */
Player hero;
int xOffset = 900;
int yOffset = 75;
float heroRotation = 270.0f;
float heroMovement = 250.0f;
/* Projectile parameters */
Projectile projectile;
sf::Vector2f projectileOffest(6.0f, -35.0f);
float startingRocketRotation = 270.0f;
float rotationSpeed = 160.0f;
float rocketSpeed = 150.0f;
/* Soldier parameters */
Soldier soldier;
sf::Vector2f soldierPosition(1024 / 2, 100);
float soldierSpeed = 200.0f;
/* Barrier parameters */
Barrier barriers[6];
int xBarrierOffset = 960;
int yBarrierOffset = 170;
int spacing = 180;

void initBindings() {
	binds.storeBinding("Shoot", sf::Keyboard::Space);
	binds.storeBinding("Left", sf::Keyboard::A);
	binds.storeBinding("Right", sf::Keyboard::D);
}

void init() {
	sf::Vector2f heroPosition(window.getSize().x - xOffset, window.getSize().y - yOffset);

	bg.init("Assets/Graphics/bg.png");
	sky.init("Assets/Graphics/sky.png");
	hero.init("Assets/Graphics/hero.png", heroPosition);
	hero.setScale(sf::Vector2f(0.5f, 0.5f));
	hero.changeRotation(heroRotation);
	projectile.disabled();
	soldier.init("Assets/Graphics/enemy.png", soldierPosition);
	soldier.setSpeed(soldierSpeed);
	soldier.changeRotation(270.0f);
	soldier.setScale(sf::Vector2f(0.8f, 0.8f));

	int length = sizeof(barriers) / sizeof(barriers[0]);
	sf::Vector2f barrierSize(90.0f, 30.0f);

	for (int i = 0; i < length; i++) {
		sf::Vector2f startPosition(window.getSize().x - xBarrierOffset + (i * spacing), window.getSize().y - yBarrierOffset);
		barriers[i].init(barrierSize, startPosition, sf::Color::Red);
	}
}

void draw() {
	window.draw(sky.getSprite());
	window.draw(bg.getSprite());
	window.draw(hero.getSprite());
	if (projectile.getStatus())
		window.draw(projectile.getSprite());
	window.draw(soldier.getSprite());

	int length = sizeof(barriers) / sizeof(barriers[0]);
	//window.draw(barriers[0].getRectangle());
	for (int i = 0; i < length; i++) {
		window.draw(barriers[i].getRectangle());
	}
}

void updateInput(float dt) {
	sf::Event event;
	int xDirection = 1;

	while (window.pollEvent(event)) {
		//Player bindings
		if (binds.validBinding("Shoot", event) && !projectile.getStatus()) {
			shoot();
			printf("Shoot\n");
		}
		if (binds.validBinding("Left", event)) {
			movement(-xDirection);
			printf("Left\n");
		}
		else if (binds.validBinding("Right", event)) {
			movement(xDirection);
			printf("Right\n");
		}

		if (event.type == sf::Event::KeyReleased) {
			movement(0);
		}

		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) {
			window.close();
		}
	}
}

void update(float dt) {
	hero.update(dt);
	soldier.update(dt);

	if(projectile.getStatus()) {
		projectile.update(dt);
		hero.setMovement(0);
		if (projectile.getOutofBounds()) {
			projectile.disabled();
			hero.setHeroMove(true);
			hero.enabled();
		}
		//If projectile has collided with enemy soldier
		if (checkCollision(projectile.getSprite(), soldier.getSprite())) {
			projectile.disabled();
			hero.setHeroMove(true);
			hero.enabled();
		}
	}
}

int main() {
	sf::Clock clock;
	window.setFramerateLimit(frameLimit);

	initBindings();
	init();

	while (window.isOpen()) {
		sf::Time dt = clock.restart();
		updateInput(dt.asSeconds());
		update(dt.asSeconds());

		window.clear(sf::Color::Red);

		draw();
		window.display();
	}

	return 0;
}
/**
 * @brief Decides movement based on if the player/projectile is active
 * 
 * @param keyDirection negative number to go left, positive number to go right
 * @param dt Delta time
 */
void movement(float keyDirection) {
	if (projectile.getStatus())
		projectile.setRotater(rotationSpeed * keyDirection);
	else
		hero.setMovement(heroMovement * keyDirection);
}
/**
 * @brief Creates a projectile object which the player will control manually
 */
void shoot() {
	projectile = Projectile();
	sf::Vector2f projectilePosition(hero.getSprite().getPosition().x + projectileOffest.x,
		hero.getSprite().getPosition().y + projectileOffest.y);

	projectile.init("Assets/Graphics/rocket.png", projectilePosition);
	projectile.changeRotation(startingRocketRotation);
	projectile.setProjectileSpeed(rocketSpeed);
	hero.setHeroMove(false);
	hero.disabled();
}
/**
 * @brief Checks if sprite1 collided with sprite2
 * 
 * @return true or false
 */
bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2) {
	sf::FloatRect shape1 = sprite1.getGlobalBounds();
	sf::FloatRect shape2 = sprite2.getGlobalBounds();

	if (shape1.intersects(shape2))
		return true;
	else
		return false;
}
