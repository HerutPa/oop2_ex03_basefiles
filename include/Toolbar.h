#pragma once

#include <SFML/Graphics/Text.hpp>
#include "Resources.h"
#include "Board.h"
#include <string>

class ToolBar
{
public:
	ToolBar();
	sf::Text& getText(int);
	sf::Text& getNum(int);
	void setAvailable(const int);
	void setLeft(const int);
	void setTake(const int);
	void setTime(const int);
	void setTimeLeft(const int);
	int getTime();

	void setSticksAvailable(int);
	void setSticksLeft(int);
	void setSticksTake(int);

private:
	//members:
	sf::Text m_toolbar[TOOL_BAR];
	sf::Text m_Info[TOOL_BAR];
	std::string m_Words[TOOL_BAR] = { "Available:", "Left:", "Take:" ,"Time:" };
	int m_info_num[TOOL_BAR];
	int m_sticksNum;
	Board m_board;
};