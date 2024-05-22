#pragma once

#include <SFML/Graphics.hpp>
#include <Resources.h>
#include "Sticks.h"
//#include "X.h"
//#include "Graph.h"


class Board
{
public:
	Board(const int, const int);
	void drawBoard(sf::RenderWindow&);
	//void setPlayerX(const Colors);
	//void setComputerX(const Colors);
	//const sf::RectangleShape getRectangle(const Colors) const;
	//const sf::Sprite getBackButton()const;
	//void backPress();
	//void backRelease();
	//const Colors getComputerColor();
	//const Colors getPlayerColor();
	//void playTurn(const bool, const Colors);
	void init();
	//const int size()const;
	//const int playerArea();
	//const int computerArea();
	//const int countArea(std::vector<bool>)const;
	//const Graph<Hexagon> getGraph()const;
	//const std::vector<Hexagon> getBoard()const;
	//void rectanglePress(Colors);
	//void rectangleRelease(Colors);

private:
	int m_row;
	int m_col;
	std::vector<Sticks> m_stick;
	//sf::RectangleShape m_grid_frame[4];
	//std::vector<sf::RectangleShape> m_rectangles;
	//std::unique_ptr<X> m_PlayerX;
	//std::unique_ptr<X
	// > m_ComputerX;
	//sf::Sprite m_back;
	Graph<Sticks> m_graph;
	sf::Sprite m_backgroung;

	////functions
	void createBoard();
	//void createRectangles();
	//void connectNeighbors();
	//void connectHexagonNeighbors(const int directions[6][2], const int, const int, Hexagon&);
	//void locateObjects();
	//void createGridFrame();
	//const sf::RectangleShape createRectangle(const int) const;
	//const Colors color2Enum(const sf::Color);
};