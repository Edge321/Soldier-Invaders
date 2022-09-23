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

void shoot();

Background bg;
Background sky;

int xOffset = 900;
int yOffset = 75;
float heroRotation = 270.0f;
float heroMovement = 250.0f;
bool canHeroMove = true;

Player hero;

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
}

void updateInput() {
	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Right && canHeroMove)
				hero.setMovement(heroMovement);
			else if (event.key.code == sf::Keyboard::Left && canHeroMove)
				hero.setMovement(-heroMovement);
			if (event.key.code == sf::Keyboard::Space)
				shoot();
		}
		else {
			hero.setMovement(0);
		}

		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) {
			window.close();
		}
	}
}

void update(float dt) {
	hero.update(dt);
}

int main() {
	sf::Clock clock;
	window.setFramerateLimit(frameLimit);

	init();

	while (window.isOpen()) {
		sf::Time dt = clock.restart();
		updateInput();
		update(dt.asSeconds());

		window.clear(sf::Color::Red);

		draw();
		window.display();
	}

	return 0;
}

void shoot() {
	Projectile* projectile = new Projectile();
}