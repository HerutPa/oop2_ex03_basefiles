#pragma once

#include <SFML/Graphics.hpp>
#include <Resources.h>
#include "Stick.h"
#include <random>



class Board
{
public:
	Board();
	void drawBoard(sf::RenderWindow&);
	void init();
	void findStick(const sf::Vector2f);

	int returnSticksAva() const;
	int returnSticksLeft()const;
	int returnSticksTake()const;


private:
	//Stick m_stickClass;

	int m_row;
	int m_col;
	int m_numOfStick;
	int m_sitckTakeCounter;
	std::vector<std::shared_ptr <Stick>> m_stick;
	sf::RectangleShape m_grid_frame[4];
	std::vector<sf::RectangleShape> m_rectangles;
	sf::Sprite m_backgroung;
    
	////functions
	void createBoard();
	void createGridFrame();
	void createRectangles();
	const sf::RectangleShape createRectangle(const int) const;
	int counter = 0;

};