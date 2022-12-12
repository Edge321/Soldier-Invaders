#include "Bindings.h"

enum InputType {
	KeyboardInput,
	MouseInput,
	Joystickinput
};
/**
 * @brief Stores a key binding to a hashmap for later use
 * 
 * @param binding Name of the key binding
 * @param keycode Key on the keyboard to be stored
 */
void Bindings::storeBinding(string binding, sf::Keyboard::Key keycode) {
	MyKeys key;

	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = keycode;
	Keys[binding] = key;
}
/**
 * @brief Returns a specified key binding (Currently not implemented)
 */
string Bindings::getBinding(string binding) {
	//return Keys[binding];
	return "NONE";
}
/**
 * @brief Checks if the key bind in question is in the stored key bindings
 * 
 * @param key Name of the key binding
 * @param event Key binding that is being pressed
 * @return true or false
 */
bool Bindings::validBinding(string key, sf::Event event) {
	MyKeys myKey = Keys[key];
	//Mouse event
	/*if (key.myInputType == MouseInput &&
		key.myEventType == event.type &&
		key.myMouseButton == event.mouseButton.button) {
		return true;
	}*/
	//Keyboard event
	if (myKey.myEventType == event.type &&
		myKey.myKeyCode == event.key.code) {
		return true;
	}

	return false;
}