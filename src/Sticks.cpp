#pragma once

#include "Sticks.h"


Sticks::Sticks(const int row, const int length)
	:  m_row(row)
{
	std::random_device rd;                       // Obtain a random seed from the hardware
	std::mt19937 generator(rd());                 // Initialize the random number generator

	std::uniform_real_distribution<float> distribution_x(0.f, 90.f); // הגדרת טווח המספרים הרנדומליים כ float
	std::uniform_real_distribution<float> distribution_y(0.f, 9.f); // הגדרת טווח המספרים הרנדומליים כ float

	float x = 300 + distribution_x(generator) * STICK_WIDTH; // יצירת מיקום אקראי עבור x
	float y = 100 + distribution_y(generator) * STICK_LENGTH; // יצירת מיקום אקראי עבור y

	std::uniform_int_distribution<int> distribution2(0, 5);  // Define the range of the random numbers
	int randomNumColor = distribution2(generator);  // Generate a random number

	std::uniform_real_distribution<float> distribution3(10.f, 355.f); // הגדרת טווח המספרים הרנדומליים כ float
	float randomNumAngel = distribution3(generator);  // Generate a random number

	m_stick.setSize(sf::Vector2f(length,150));
	m_stick.setOrigin(0, 0);
	m_stick.setOrigin(25, 25);
	m_stick.setPosition(x,y);
	m_stick.setRotation(randomNumAngel);
	m_stick.setFillColor(Resources::instance().getColorArray()[randomNumColor]);
	m_stick.setOutlineThickness(OUTLINE);
	m_stick.setOutlineColor(sf::Color::Black);
}


sf::RectangleShape& Sticks::get()
{
	return m_stick;
}


const int Sticks::getRow()const
{
	return m_row;
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

void Sticks::setColor(const Colors color)
{
	m_stick.setFillColor(Resources::instance().getColorArray()[color]);
}

