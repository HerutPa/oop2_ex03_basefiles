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
	m_stick.clear();
	//m_graph.clear();
	createBoard();
	//connectNeighbors();
}

void Board::createBoard()
{
	for (int row = 0; row < m_row; ++row)
	{
		for (int col = 0; col < m_col; ++col)
		{
			m_stick.push_back(Sticks(row, col));
		}
	}
	if (m_stick[m_col - 1].getColor() == m_stick[m_row * m_col - m_col].getColor())
	{
		m_stick[COMPUTER_INDEX].get().setFillColor(Resources::instance().getColorArray()[Cyan]);
		m_stick[PLAYER_INDEX].get().setFillColor(Resources::instance().getColorArray()[Blue]);
	}
}

//איך לצייר את תחילת המשחק . לפי מה ?
void Board::drawBoard(sf::RenderWindow& window)
{
	window.draw(m_backgroung);
	/*for (int stick = 0; stick < m_stick.size(); stick++)
	{
		window.draw(m_stick[stick].get());
	}
	for (int rectangle = 0; rectangle < 4; rectangle++)
	{
		window.draw(m_grid_frame[rectangle]);
	}
	for (int rectangle = 0; rectangle < m_rectangles.size(); rectangle++)
	{
		window.draw(m_rectangles[rectangle]);
	}*/

	//window.draw(m_back);
}