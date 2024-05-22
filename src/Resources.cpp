#pragma once

#include "Resources.h"

Resources::Resources()
{
	LoadFromFile();
}

Resources& Resources::instance()
{
	static Resources Resource;
	return Resource;
}

const sf::Color* Resources::getColorArray()const
{
	return m_colorArray;
}

const sf::Texture& Resources::getTexture(const Textures texture)const
{
	return m_textures[texture];
}

const sf::Texture& Resources::getButton(const Button button)const
{
	return m_Buttons[button];
}

const sf::Font& Resources::getFont()const
{
	return m_font;
}

void Resources::LoadFromFile()
{
	m_textures[X_texture].loadFromFile("X.png");
	m_textures[Background].loadFromFile("Background.png");
	m_textures[Background].setSmooth(true);
	m_textures[Back].loadFromFile("Back.png");
	m_textures[Six_colors].loadFromFile("Six_colors.png");
	m_textures[GameBackground].loadFromFile("GameBackground.png");
	m_textures[GameBackground].setSmooth(true);
	m_textures[YouWin].loadFromFile("YouWin.png");
	m_textures[YouLose].loadFromFile("YouLose.png");

	m_Buttons[Easy].loadFromFile("Easy.png");
	m_Buttons[Medium].loadFromFile("Medium.png");
	m_Buttons[Hard].loadFromFile("Hard.png");

	m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}
