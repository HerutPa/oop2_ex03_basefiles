#pragma once

#include "Sticks.h"


Sticks::Sticks(const int row, const int col)
	:m_row(row), m_col(col), m_stick(RADIUS, 6)
{
	std::random_device rd;                       // Obtain a random seed from the hardware
	std::mt19937 generator(rd());                 // Initialize the random number generator
	std::uniform_int_distribution<int> distribution(0, 5);  // Define the range of the random numbers

	int randomNumber = distribution(generator);  // Generate a random number

	m_stick.setOrigin(0, 0);
	m_stick.setOrigin(25, 25);
	m_stick.setPosition(getPosition());
	m_stick.setFillColor(Resources::instance().getColorArray()[randomNumber]);
	m_stick.setOutlineThickness(OUTLINE);
	m_stick.setOutlineColor(sf::Color::Black);
}

sf::CircleShape& Sticks::get()
{
	return m_stick;
}



const int Sticks::getRow()const
{
	return m_row;
}

const int Sticks::getCol()const
{
	return m_col;
}




const sf::Color Sticks::getColor()const
{
	return m_stick.getFillColor();
}



const sf::Vector2f Sticks::getPosition()const
{
	float x = m_col * HEX_WIDTH + ((m_row % 2 == 0) ? HEX_WIDTH / 2.f : 0.f) + (WINDOW_WIDTH/2)- (GRID_WIDTH/2) + RADIUS;
	float y = (m_row * (HEX_HEIGHT * 3.f / 4.f) + (WINDOW_HEIGHT / 2) - (GRID_HEGHT / 2));

	return sf::Vector2f(x, y);
}

const int Sticks::getIndex()const
{
	return COL * m_row + m_col;
}

void Sticks::setColor(const Colors color)
{
	m_stick.setFillColor(Resources::instance().getColorArray()[color]);
}
