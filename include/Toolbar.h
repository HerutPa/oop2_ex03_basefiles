#pragma once

#include <SFML/Graphics/Text.hpp>
#include "Resources.h"
#include "Board.h"
#include <string>

class ToolBar
{
public:
	ToolBar();
	int getScoreFinish();
	void init();
	void drawToolBar(sf::RenderWindow& m_window);
	bool isButtonPrasedSave(sf::Vector2f location);
	bool isButtonPrasedHint(sf::Vector2f location);
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
	std::string m_Words[TOOL_BAR] = {"Score:", "Available:", "Left:", "Take:" ,"Time:"};
	int m_info_num[TOOL_BAR];
	int m_sticksNum;
	Board m_board;
	sf::RectangleShape m_outline;
	sf::RectangleShape m_recHint;
	sf::RectangleShape m_recSave;
	sf::Texture m_textureS;
	sf::Texture m_textureH;
	char m_type = 'S';
};