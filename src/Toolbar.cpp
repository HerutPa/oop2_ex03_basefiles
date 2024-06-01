#pragma once
#include "ToolBar.h"


ToolBar::ToolBar()
{
	//set the word:
	for (int word = AVAILABLE; word <= TIME; word++)
	{
		m_toolbar[word].setFont(Resources::instance().getFont());
		m_toolbar[word].setCharacterSize(30);
		m_toolbar[word].setString(m_Words[word]);
		m_toolbar[word].setFillColor(sf::Color::Blue);
		m_toolbar[word].setPosition(100.f, word * 150.f + 50);
	}

	m_info_num[AVAILABLE] = m_board.returnSticksAva();
	m_info_num[LEFT] = m_board.returnSticksLeft();
	m_info_num[TAKE] = 0;
	m_info_num[TIME] = 0;

	for (int word = AVAILABLE; word <= TIME; word++)
	{
		m_Info[word].setFont(Resources::instance().getFont());
		m_Info[word].setCharacterSize(30);
		m_Info[word].setString(std::to_string(m_info_num[word]));
		m_Info[word].setFillColor(sf::Color::Green);
		m_Info[word].setPosition(100.f, 40 + word * 150.f + 50);
	}	
}

void ToolBar::init()
{
	//toolbar position
	m_outline.setSize(sf::Vector2(100.f, 100.f));
	m_outline.setPosition(0.f, 0.f);

	//Style
	m_outline.setOutlineColor(sf::Color::Color(0, 0, 0));
	m_outline.setOutlineThickness(4.f);
	m_outline.setFillColor(sf::Color::Color(255, 255, 255));

	m_rec.setSize(sf::Vector2f(100.f, 100.f));
	m_texture.loadFromFile("save.png");
	m_rec.setTexture(&m_texture);
	m_rec.setPosition(sf::Vector2f(0, 0));

}

void ToolBar::drawToolBar(sf::RenderWindow& m_window)
{
	m_window.draw(m_outline);
	m_window.draw(m_rec);
}

sf::Text& ToolBar::getText(int word)
{
	return m_toolbar[word];
}

sf::Text& ToolBar::getNum(int num)
{
	return m_Info[num];
}

void ToolBar::setTime(const int time)
{
	m_info_num[TIME] = 40 - time;
	m_Info[TIME].setString(std::to_string(m_info_num[TIME]));
}

void ToolBar::setTimeLeft(const int time)
{
	m_info_num[TIME] = time;
	m_Info[TIME].setString(std::to_string(m_info_num[TIME]));
}

int ToolBar::getTime()
{
	return m_info_num[TIME];
}

void ToolBar::setSticksAvailable(int available)
{
	m_info_num[AVAILABLE] = available;
	m_Info[AVAILABLE].setString(std::to_string(available));
}

void ToolBar::setSticksLeft(int left)
{
	m_info_num[LEFT] = left;
	m_Info[LEFT].setString(std::to_string(left));
}

void ToolBar::setSticksTake(int take)
{
	m_info_num[TAKE] = take;
	m_Info[TAKE].setString(std::to_string(take));
}

