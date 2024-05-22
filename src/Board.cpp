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
