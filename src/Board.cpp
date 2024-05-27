#pragma once

#include "Board.h"
#include <iostream>


Board::Board(/*const int row, const int col*/)
	//:m_row(row), m_col(col)/*, m_graph(row* col)*/
{
	
	//m_backgroung.setTexture(Resources::instance().getTexture(GameBackground));
	//m_backgroung.scale(2.6f, 2.6f);
	createRectangles();
	//createGridFrame();
	//locateObjects();
	std::random_device rd; // מקור למספרים רנדומליים
	std::mt19937 gen(rd()); // מחולל מספרים רנדומליים ממשפחת mersenne_twister_engine
	std::uniform_int_distribution<int> dis(30, 50); // פיזור אחיד של מספרים בין 30 ל־50
	m_numOfStick = dis(gen); // השמה של מספר רנדומלי ל־m_numOfStic
}

void Board::createRectangles()
{
	for (int rectangle = 0; rectangle < 6; ++rectangle)
	{
		m_rectangles.push_back(createRectangle(rectangle));
	}
}


const sf::RectangleShape Board::createRectangle(const int index) const
{
	sf::RectangleShape rec;

	//Position
	rec.setSize(sf::Vector2f(50.f, 50.f));
	rec.setPosition(WINDOW_WIDTH * 0.5 - 300 + index * 100, WINDOW_HEIGHT * 0.9);

	//Style
	rec.setOutlineThickness(2.f);
	rec.setFillColor(Resources::instance().getColorArray()[index]);

	return rec;
}

void Board::init()
{
	m_sticks.clear();
	//m_graph.clear();
	createBoard();
	//connectNeighbors();
}

void Board::createBoard()
{
	for (int row = 0; row < m_numOfStick; ++row)
	{
		auto temp = std::make_shared<Sticks>(row, 5);
		
		for (const auto& stick1 : m_sticks)
		{
			if (Sticks::isOverlaped(*temp.get(), *stick1.get()))
			{
				temp.get()->addOverLapped(stick1);
				stick1.get()->addOverLapped(temp);
			}
		}
		m_sticks.push_back(temp);

	}


	/*if (m_stick[m_col - 1].getColor() == m_stick[m_row * m_col - m_col].getColor())
	{
		m_stick[COMPUTER_INDEX].get().setFillColor(Resources::instance().getColorArray()[Cyan]);
		m_stick[PLAYER_INDEX].get().setFillColor(Resources::instance().getColorArray()[Blue]);
	}*/
}

//איך לצייר את תחילת המשחק . לפי מה ?
void Board::drawBoard(sf::RenderWindow& window)
{
	//window.clear();
	window.clear(sf::Color::Color(210, 210, 210));
	for (int stick = 0; stick < m_sticks.size(); stick++)
	{
		window.draw(m_sticks[stick]->getrec());
	}
	/*for (int rectangle = 0; rectangle < 4; rectangle++)
	{
		window.draw(m_grid_frame[rectangle]);
	}*/
	//for (int rectangle = 0; rectangle < m_rectangles.size(); rectangle++)
	//{
	//	window.draw(m_rectangles[rectangle]);
	//}*/

	//window.draw(m_back);
}

//void Board::createGridFrame()
//{
//	//up
//	m_grid_frame[0].setSize(sf::Vector2f(GRID_WIDTH + RADIUS, 3 / 2 * RADIUS));
//	m_grid_frame[0].setFillColor(WINDOW_COLOR);
//	m_grid_frame[0].setPosition(sf::Vector2f((WINDOW_WIDTH / 2) - (GRID_WIDTH / 2) - RADIUS,
//		(WINDOW_HEIGHT / 2) - (GRID_HEGHT / 2) - 2 * RADIUS + 2 * OUTLINE));
//	//down
//	m_grid_frame[1].setSize(sf::Vector2f(GRID_WIDTH + RADIUS, 3 / 2 * RADIUS));
//	m_grid_frame[1].setFillColor(WINDOW_COLOR);
//	m_grid_frame[1].setPosition(sf::Vector2f((WINDOW_WIDTH / 2) - (GRID_WIDTH / 2) - RADIUS,
//		(WINDOW_HEIGHT / 2) + (GRID_HEGHT / 2) - 2 * RADIUS - 2 * OUTLINE));
//	//right
//	m_grid_frame[2].setSize(sf::Vector2f(2 * RADIUS, GRID_HEGHT + RADIUS - 4 * OUTLINE));
//	m_grid_frame[2].setFillColor(WINDOW_COLOR);
//	m_grid_frame[2].setPosition(sf::Vector2f((WINDOW_WIDTH / 2) + (GRID_WIDTH / 2) - RADIUS - (STICK_WIDTH / 2) + 3 * OUTLINE + RADIUS,
//		(WINDOW_HEIGHT / 2) - (GRID_HEGHT / 2) - 2 * RADIUS + 2 * OUTLINE));
//	//lrft
//	m_grid_frame[3].setSize(sf::Vector2f(2 * RADIUS, GRID_HEGHT + RADIUS - 4 * OUTLINE));
//	m_grid_frame[3].setFillColor(WINDOW_COLOR);
//	m_grid_frame[3].setPosition(sf::Vector2f((WINDOW_WIDTH / 2) - (GRID_WIDTH / 2) - 2 * (RADIUS + 2 * OUTLINE) + STICK_WIDTH / 2 - 4 * OUTLINE,
//		(WINDOW_HEIGHT / 2) - (GRID_HEGHT / 2) - 2 * RADIUS + 2 * OUTLINE));
//}