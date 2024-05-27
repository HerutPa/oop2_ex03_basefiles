#pragma once

#include <SFML/Graphics.hpp>
#include <Resources.h>
#include "Sticks.h"
#include <random>



class Board
{
public:
	Board();
	void drawBoard(sf::RenderWindow&);
	void init();


private:
	int m_row;
	int m_col;
	int m_numOfStick;
	std::vector<std::shared_ptr <Sticks>> m_sticks;
	sf::RectangleShape m_grid_frame[4];
	std::vector<sf::RectangleShape> m_rectangles;
	sf::Sprite m_backgroung;
    
	////functions
	void createBoard();
	void createRectangles();
	const sf::RectangleShape createRectangle(const int) const;

};