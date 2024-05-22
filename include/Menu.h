#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Resources.h>

class Menu
{
public:
	Menu();
	sf::Sprite getButton(const Button) const;
	void drawMenu(sf::RenderWindow&)const;
	void ButtonPress(const Button);
	void ButtonRelease(const Button);

private:

	sf::Sprite m_backgroung;
	sf::Sprite m_buttons[BUTTONS];
	sf::Sprite m_back_buttons[BUTTONS];
	sf::Sprite m_label;

	void locateObjects();
};
