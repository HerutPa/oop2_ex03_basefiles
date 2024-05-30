#pragma once

#include "Stick.h"

//אנחנו רוצים לייצר וקטור של הדוקים שכל אחד מהם ידע לחשב כלפי כל דוק שהודפס לפניו האם הוא נוגע בו מעליו.
//2 יבדוק את 1 ואם הוא מעליו אז ל1 יירשם שיש משהו מעליו 
//3 יבדוק את 2 ואז גם את 1 ויסמן לכל אחד מהם בהתאמה האם מספר 3 נמצא מעליו.
Stick::Stick(const int row, const int length)
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
	m_location.x = x;
	m_location.y = y;
	setBounds(x, y, STICK_WIDTH, length);
}


void Stick::setBounds(float x, float y, float STICK_WIDTH, float length)
{
	m_bounds.left = x;
	m_bounds.top = y;
	m_bounds.width = STICK_WIDTH;
	m_bounds.height = length;
}

sf::RectangleShape& Stick::getrec()
{
	return m_stick;
}


const int Stick::getRow()const
{
	return m_row;
}


const sf::Color Stick::getColor()const
{
	return m_stick.getFillColor();
}

const sf::Vector2f Stick::getLocation() const
{
	return m_location;
}



void Stick::setColor(const Colors color)
{
	m_stick.setFillColor(Resources::instance().getColorArray()[color]);
}

bool Stick::isOverlaped(const Stick& stick1, const Stick& stick2)
{
	return true;//algooritem
}

void Stick::addOverLapped(const std::shared_ptr<Stick> &overlap)
{
	m_overlapped.push_back(overlap);
}



