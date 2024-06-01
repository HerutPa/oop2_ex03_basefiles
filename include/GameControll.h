#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include "Algorithm.h"
#include "Resources.h"
#include "Board.h"
#include "Menu.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <Toolbar.h>
#include <chrono>
#include <thread>



class GameControll
{
public:
	GameControll();
	void run();
	


private:
	sf::RenderWindow m_window;
//	Resources& m_resource = Resources::instance();
	Menu m_menu;
	Board m_board;
	ToolBar m_toolBar;

	bool m_game_over;
//	std::unique_ptr<Algorithm> m_algorithm;
	sf::Sprite m_YouWin;
	sf::Sprite m_YouLose;
	sf::Text m_score[2];
//
//	//functions
//	void playerTurn(const sf::Vector2f);
	void handleMenuClick(const sf::Vector2f);
	void handleMenuMouseMoved(const sf::Vector2f);
//	void handleGameMouseMoved(const sf::Vector2f);
	void startGame();
	void handleClick(const sf::Vector2f& location);
	void UpdateData();
	void init();
	void drawToolBar();
	void continueGame();
//	void computerTurn(Colors);
//	void winLoop();
//	void loseLoop();
	//void locateObjects();
	sf::Clock m_GameClock;
	sf::Clock m_MoveClock;
	ToolBar m_toolbar;
	std::ifstream m_ifile = std::ifstream("Board.txt");
	std::ofstream m_ofile;
	sf::Sprite m_youWin;
	sf::Sprite m_youLose;
};