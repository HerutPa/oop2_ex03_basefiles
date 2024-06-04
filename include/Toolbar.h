#pragma once
#include <SFML/Graphics/Text.hpp>
#include "Resources.h"
#include "Board.h"
#include <string>


class ToolBar
{
public:
	ToolBar();
	void drawToolBar(sf::RenderWindow& m_window);
	void setSticksAvailable(int);
	void setTimeLeft(const int);
	void setSticksLeft(int);
	void setSticksTake(int);
	void setScore(int take);
	void setTime(const int);
	void init();

	bool isButtonPrasedSave(sf::Vector2f location);
	bool isButtonPrasedHint(sf::Vector2f location);

	sf::FloatRect getGlobalBounds()const { return m_outline.getGlobalBounds(); }
	sf::Text& getText(int);
	sf::Text& getNum(int);

	int getTime();

private:
	Board m_board;

	int m_info_num[TOOL_BAR];
	int m_sticksNum;

	sf::RectangleShape m_outline;
	sf::RectangleShape m_recHint;
	sf::RectangleShape m_recSave;
	sf::Text m_toolbar[TOOL_BAR];
	sf::Text m_Info[TOOL_BAR];
	sf::Texture m_textureS;
	sf::Texture m_textureH;

	std::string m_Words[TOOL_BAR] = { "Score:", "Available:", "Left:", "Take:" ,"Time:" };
};
	