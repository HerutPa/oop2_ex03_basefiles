#pragma once

#include <SFML/Graphics/Text.hpp>
#include "Resources.h"
#include "Board.h"
#include <string>

class ToolBar
{
public:
	ToolBar();
	void init();
	void drawToolBar(sf::RenderWindow& m_window);
	sf::Text& getText(int);
	sf::Text& getNum(int);
	void setTime(const int);
	void setTimeLeft(const int);
	int getTime();

	void setSticksAvailable(int);
	void setSticksLeft(int);
	void setSticksTake(int);
	sf::FloatRect getGlobalBounds()const { return m_outline.getGlobalBounds(); }


private:
	//members:
	sf::Text m_toolbar[TOOL_BAR];
	sf::Text m_Info[TOOL_BAR];
	std::string m_Words[TOOL_BAR] = { "Available:", "Left:", "Take:" ,"Time:" };
	int m_info_num[TOOL_BAR];
	int m_sticksNum;
	Board m_board;
	sf::RectangleShape m_outline;
	sf::RectangleShape m_rec;
	sf::Texture m_texture;
	char m_type = 'S';
};