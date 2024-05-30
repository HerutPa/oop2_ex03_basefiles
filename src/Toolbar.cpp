//#pragma once
//
//#include "ToolBar.h"
//
//ToolBar::ToolBar()
//{
//	//set the word:
//	for (int word = AVAILABLE; word <= TIME; word++)
//	{
//		m_toolbar[word].setFont(Resources::instance().getFont());
//		m_toolbar[word].setCharacterSize(30);
//		m_toolbar[word].setString(m_Words[word]);
//		m_toolbar[word].setFillColor(sf::Color::Green);
//		m_toolbar[word].setPosition(1200.f, word * 150.f + 50);
//	}
//	//set the num:
//	m_info_num[AVAILABLE] = m_board.getAvailable();
//	m_info_num[SCORE] = 0;
//	m_info_num[LEFT] = m_board.getNumOfStick();
//	m_info_num[TAKE] = 0;
//	m_info_num[TIME] = 0;
//
//	for (int word = AVAILABLE; word <= TIME; word++)
//	{
//		m_Info[word].setFont(Resources::instance().getFont());
//		m_Info[word].setCharacterSize(30);
//		m_Info[word].setString(std::to_string(m_info_num[word]));
//		m_Info[word].setFillColor(sf::Color::Green);
//		m_Info[word].setPosition(1200.f, 40 + word * 150.f + 50);
//	}
//}
//
//sf::Text& ToolBar::GetText(int word)
//{
//	return m_toolbar[word];
//}
//
//sf::Text& ToolBar::GetNum(int num)
//{
//	return m_Info[num];
//}
//
//int ToolBar::GetScore()
//{
//	return m_info_num[SCORE];
//}
//
//int ToolBar::GetTime()
//{
//	return m_info_num[TIME];
//}
//
//int ToolBar::GetAvailable()
//{
//	return m_info_num[AVAILABLE];
//}
//
//
//void ToolBar::setAvailable(const int available)
//{
//	m_info_num[AVAILABLE] = available;
//	m_Info[AVAILABLE].setString(std::to_string(available));
//}
//
//void ToolBar::SetScore(const int score)
//{
//	m_info_num[SCORE] = score;
//	m_Info[SCORE].setString(std::to_string(score));
//}
//
//void ToolBar::SetLeft(const int left)
//{
//	m_info_num[LEFT] = left;
//	m_Info[LEFT].setString(std::to_string(left));
//}
//
//void ToolBar::SetTake(const int take)
//{
//	m_info_num[TAKE] = take;
//	m_Info[TAKE].setString(std::to_string(take));
//}
//
//void ToolBar::SetTime(const int time)
//{
//	m_info_num[TIME] = 40 - time;// +m_mouse.getTime();
//	m_Info[TIME].setString(std::to_string(m_info_num[TIME]));
//}
//
