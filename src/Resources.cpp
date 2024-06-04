#include "Resources.h"


Resources::Resources()
{
	LoadFromFile();
}

//Singleton 
Resources& Resources::instance()
{
	static Resources Resource;
	return Resource;
}

//return m_colorArray
const sf::Color* Resources::getColorArray()const
{
	return m_colorArray;
}

//return the picture
const sf::Texture& Resources::getTexture(const Textures texture)const
{
	return m_textures[texture];
}

//return the button
const sf::Texture& Resources::getButton(const Button button)const
{
	return m_Buttons[button];
}

//return the font
const sf::Font& Resources::getFont()const
{
	return m_font;
}

//Load From File
void Resources::LoadFromFile()
{
	m_textures[X_texture].loadFromFile("X.png");
	m_textures[Background].loadFromFile("Background.png");
	m_textures[Background].setSmooth(true);
	m_textures[Back].loadFromFile("Back.png");
	m_textures[Label].loadFromFile("Label.png");
	m_textures[GameBackground].loadFromFile("GameBackground.png");
	m_textures[GameBackground].setSmooth(true);
	m_textures[YouWin].loadFromFile("YouWin.png");
	m_textures[YouWin].setSmooth(true);
	m_textures[YouLose].loadFromFile("YouLose.png");
	m_textures[YouLose].setSmooth(true);

	m_Buttons[Play].loadFromFile("Play.png");
	m_Buttons[Continue].loadFromFile("Continue.png");
	m_Buttons[Exit].loadFromFile("Exit.png");

	m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}
