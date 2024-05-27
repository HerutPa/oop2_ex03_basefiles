//#pragma once
//
//#include <SFML/Graphics/Text.hpp>
//#include "Resources.h"
//#include <string>
//
//class ToolBar
//{
//public:
//	ToolBar();
//	sf::Text& GetText(int);
//	sf::Text& GetNum(int);
//	void setAvailable(const int);
//	void SetScore(const int);
//	void SetLeft(const int);
//	void SetTake(const int);
//	void SetTime(const int);
//	int GetScore();
//	int GetTime();
//	int GetAvailable();
//
//private:
//	//members:
//	sf::Text m_toolbar[TOOL_BAR];
//	sf::Text m_Info[TOOL_BAR];
//	std::string m_Words[TOOL_BAR] = { "Available:" , "Score:", "Left:", "Take:" ,"Time:" };
//	int m_info_num[TOOL_BAR];
//};