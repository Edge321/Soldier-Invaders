#include <SFML/Graphics.hpp>
#include "Background.h"
#include "Character.h"
#include "Player.h"
#include "Projectile.h"

/*
The game to make: can guide your missile, space invaders-like
*/

sf::Vector2i windowSize(1024, 768);
sf::VideoMode vm(windowSize.x, windowSize.y);
sf::RenderWindow window(vm, "Hello Everybody!", sf::Style::Default);

int frameLimit = 60;

//Shmovement
void movement(float xDirection, float dt);
void shoot();

Background bg;
Background sky;

int xOffset = 900;
int yOffset = 75;
float heroRotation = 270.0f;
float heroMovement = 250.0f;
bool canHeroMove = true;

Player hero;

Projectile* projectile;
sf::Vector2f projectileOffest(10.0f, -50.0f);
float rocketRotation = 270.0f;
float rotationSpeed = 500.0f;
float rocketSpeed = 100.0f;
bool canRocketMove = false;

void init() {
	sf::Vector2f heroPosition(window.getSize().x - xOffset, window.getSize().y - yOffset);

	bg.init("Assets/Graphics/bg.png");
	sky.init("Assets/Graphics/sky.png");
	hero.init("Assets/Graphics/hero.png", heroPosition);
	hero.changeRotation(heroRotation);
}

void draw() {
	window.draw(sky.getSprite());
	window.draw(bg.getSprite());
	window.draw(hero.getSprite());
	if (projectile != nullptr)
		window.draw(projectile->getSprite());
}

void updateInput(float dt) {
	sf::Event event;
	int xDirection = 1;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Right)
				movement(xDirection, dt);
			if (event.key.code == sf::Keyboard::Left)
				movement(-xDirection, dt);
			if (event.key.code == sf::Keyboard::Space)
				shoot();
		}
		//Bug: character freezes if player quickly alternating left and right arrow keys
		if (event.type == sf::Event::KeyReleased) {
			hero.setMovement(0);
		}

		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) {
			window.close();
		}
	}
}

void update(float dt) {
	hero.update(dt);
	//Prevents program from crashing if rocket does not exist
	if (projectile != nullptr)
		projectile->update(dt);
}

int main() {
	sf::Clock clock;
	window.setFramerateLimit(frameLimit);

	init();

	while (window.isOpen()) {
		sf::Time dt = clock.restart();
		updateInput(dt.asSeconds());
		update(dt.asSeconds());

		window.clear(sf::Color::Red);

		draw();
		window.display();
	}

	delete(projectile);

	return 0;
}

void movement(float keyDirection, float dt) {
	if (canHeroMove)
		hero.setMovement(heroMovement * keyDirection);
	else
		projectile->rotate(rocketRotation * keyDirection * dt);
}

void shoot() {
	projectile = new Projectile();
	sf::Vector2f projectilePosition(hero.getSprite().getPosition().x + projectileOffest.x,
		hero.getSprite().getPosition().y + projectileOffest.y);

	projectile->init("Assets/Graphics/rocket.png", projectilePosition);
	projectile->changeRotation(rocketRotation);
	projectile->setProjectileSpeed(rocketSpeed);
	canHeroMove = false;
	hero.disabled();
}