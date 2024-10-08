#include "Menu.h"


Menu::Menu()
{
	//The background of the first window in the game
	m_backgroung.setTexture(Resources::instance().getTexture(Background));
	m_backgroung.scale(0.8f, 0.8f);
	m_label.setTexture(Resources::instance().getTexture(Label));
	//the buttons
	for (int button = Play; button <= Exit; button++)
	{
		m_buttons[button].setTexture(Resources::instance().getButton((Button)button));
		m_back_buttons[button].setTexture(Resources::instance().getButton((Button)button));
	}
	locateObjects();
}

//The drawing of the buttons
sf::Sprite Menu::getButton(const Button button) const
{
	return m_buttons[button];
}

//The drawing of the all window
void Menu::drawMenu(sf::RenderWindow& window)const
{
	window.draw(m_backgroung);
	for (int button = Play; button <= Exit; button++)
	{
		window.draw(m_back_buttons[button]);
		window.draw(m_buttons[button]);
	}
	window.draw(m_label);
}

//This function changes the color of the button as soon as the user hovers over it with the mouse
void Menu::ButtonPress(const Button button)
{
	m_buttons[button].setColor(sf::Color::Color(255, 255, 255, 150));
}

//This function changes the color of the button as soon as the user removes the mouse from the button
void Menu::ButtonRelease(const Button button)
{
	m_buttons[button].setColor(sf::Color::Color(255, 255, 255));
}

//This function is responsible for the position of the buttons in the menu
void Menu::locateObjects()
{
	m_buttons[Play].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Play].getTextureRect().width) * 0.5,
		WINDOW_HEIGHT - m_buttons[Play].getTextureRect().height * 1.5 * 3));

	m_buttons[Continue].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Continue].getTextureRect().width) * 0.5,
		WINDOW_HEIGHT - m_buttons[Continue].getTextureRect().height * 1.5 * 2));

	m_buttons[Exit].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Exit].getTextureRect().width) * 0.5,
		WINDOW_HEIGHT - m_buttons[Exit].getTextureRect().height * 1.5 * 1));

	m_back_buttons[Play].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Play].getTextureRect().width) * 0.5,
		WINDOW_HEIGHT - m_buttons[Play].getTextureRect().height * 1.5 * 3));

	m_back_buttons[Continue].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Continue].getTextureRect().width) * 0.5,
		WINDOW_HEIGHT - m_buttons[Continue].getTextureRect().height * 1.5 * 2));

	m_back_buttons[Exit].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Exit].getTextureRect().width) * 0.5,
		WINDOW_HEIGHT - m_buttons[Exit].getTextureRect().height * 1.5 * 1));

	m_back_buttons[Play].setColor(sf::Color::Green);
	m_back_buttons[Continue].setColor(sf::Color::Blue);
	m_back_buttons[Exit].setColor(sf::Color::Color(255, 119, 0));

	m_label.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.1));

	m_label.scale(sf::Vector2f(WINDOW_WIDTH * 0.5 / m_label.getTextureRect().width,
		WINDOW_WIDTH * 0.5 / m_label.getTextureRect().width));
}
