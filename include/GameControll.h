#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Toolbar.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <chrono>
#include <thread>
#include "Resources.h"
#include "Board.h"
#include "Menu.h"


class GameControll
{
public:
	GameControll();
	void run();
	
private:
	sf::RenderWindow m_window;
	ToolBar m_toolBar;
	Board m_board;
	Stick m_stick; 
	Menu m_menu;

	std::ifstream m_ifile = std::ifstream("Board.txt");
	std::ofstream m_ofile;

	sf::Clock m_GameClock;
	sf::Clock m_MoveClock;
	
	sf::Sprite m_youWin;
	sf::Sprite m_youLose;
	sf::Sprite m_YouWin;
	sf::Sprite m_YouLose;

	sf::Text m_score[2];

	bool m_game_over;

	//functions
	void handleClick(const sf::Vector2f& location);
	void handleMenuMouseMoved(const sf::Vector2f);
	void handleMenuClick(const sf::Vector2f);
	void continueGame();
	void drawToolBar();
	void UpdateData();
	void startGame();
	void init();
	
};