#pragma once

#include "Sticks.h"


Sticks::Sticks(const int row, const int col, const int length)
	: m_col(col), m_row(row)
{
	std::random_device rd;                       // Obtain a random seed from the hardware
	std::mt19937 generator(rd());                 // Initialize the random number generator
	std::uniform_int_distribution<int> distribution(0, 120);  // Define the range of the random numbers
	std::uniform_int_distribution<int> distribution2(0, 5);  // Define the range of the random numbers
	//std::uniform_real_distribution<float> distribution(0.f, 1.f); // הגדרת טווח המספרים הרנדומליים
	float x = distribution(generator) * STICK_WIDTH; // יצירת מיקום אקראי עבור x
	float y = distribution(generator) * STICK_LENGTH; // יצירת מיקום אקראי עבור y


	int randomNumber = distribution(generator);  // Generate a random number
	int randomNumber2 = distribution2(generator);  // Generate a random number

	m_stick.setSize(sf::Vector2f(length,150));
	m_stick.setOrigin(0, 0);
	m_stick.setOrigin(25, 25);
	m_stick.setPosition(x,y);
	m_stick.setFillColor(Resources::instance().getColorArray()[randomNumber2]);
	m_stick.setOutlineThickness(OUTLINE);
	m_stick.setOutlineColor(sf::Color::Black);
}

//const sf::Vector2f Sticks::getPosition()const
//{
//
//	//float x = distribution(generator) * STICK_WIDTH; // יצירת מיקום אקראי עבור x
//	//float y = distribution(generator) * STICK_LENGTH; // יצירת מיקום אקראי עבור y
//	//return sf::Vector2f(x, y); // החזרת המיקום כ vektor
//}


sf::RectangleShape& Sticks::get()
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


//const sf::Vector2f Sticks::getPosition()const
//{
//	float x = m_col * STICK_WIDTH + ((m_row % 2 == 0) ? STICK_WIDTH / 2.f : 0.f) + (WINDOW_WIDTH/2)- (GRID_WIDTH/2) + RADIUS;
//	float y = (m_row * (STICK_LENGTH * 3.f / 4.f) + (WINDOW_HEIGHT / 2) - (GRID_HEGHT / 2));
//
//	return sf::Vector2f(x, y);
//}

const int Sticks::getIndex()const
{
	return COL * m_row + m_col;
}

void Sticks::setColor(const Colors color)
{
	m_stick.setFillColor(Resources::instance().getColorArray()[color]);
}

