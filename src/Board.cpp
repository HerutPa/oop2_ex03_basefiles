#pragma once

#include "Board.h"


Board::Board(const int row, const int col)
	:m_row(row), m_col(col)/*, m_graph(row* col)*/
{
	m_backgroung.setTexture(Resources::instance().getTexture(GameBackground));
	m_backgroung.scale(2.6f, 2.6f);
	//createRectangles();
	//createGridFrame();
	//locateObjects();
}

void Board::init()
{
	m_hexagons.clear();
	m_graph.clear();
	createBoard();
	connectNeighbors();
	m_ComputerX = std::make_unique<X>(m_rectangles[color2Enum(m_hexagons[COMPUTER_INDEX].getColor())].getPosition());
	m_PlayerX = std::make_unique<X>(m_rectangles[color2Enum(m_hexagons[PLAYER_INDEX].getColor())].getPosition());
}
