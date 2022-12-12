/*********************************************************************
 * @file   Bindings.h
 * @brief  Keeps track of all key bindings
 * 
 * @author Edge321
 * @date   December 2022
 *********************************************************************/

#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
#pragma once
class Bindings
{
public:
	struct MyKeys {
		//InputType myInputType;
		sf::Event::EventType myEventType;
		sf::Keyboard::Key myKeyCode;
		//sf::Mouse::Button myMouseButton;
	};

	void storeBinding(string binding, sf::Keyboard::Key);
	string getBinding(string binding);
	bool validBinding(string key, sf::Event event);

private:
	map<string, MyKeys> Keys;
};

