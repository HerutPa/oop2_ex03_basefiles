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
	bool m_game_over;
//	std::unique_ptr<Algorithm> m_algorithm;
	sf::Sprite m_YouWin;
	sf::Sprite m_YouLose;
	sf::Text m_score[2];
//
//	//functions
//	void playerTurn(const sf::Vector2f);
//	void handleMenuClick(const sf::Vector2f);
//	void handleMenuMouseMoved(const sf::Vector2f);
//	void handleGameMouseMoved(const sf::Vector2f);
//	void startGame();
//	void init();
//	void computerTurn(Colors);
//	void winLoop();
//	void loseLoop();
	void locateObjects();
};