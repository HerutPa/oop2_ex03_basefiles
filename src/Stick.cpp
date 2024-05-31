#pragma once
#include "Stick.h"


Stick::Stick(const int row, const int length)
//	:  m_index(row)
{
	m_index = row;
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
	
}





sf::RectangleShape& Stick::getrec() const
{
	return const_cast<sf::RectangleShape&>(m_stick);
}

const int Stick::getIndex()const
{
	return m_index;
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
	Point p1 = { stick1.getLocation().x, stick1.getLocation().y };
	Point q1 = { stick1.getLocation().x + stick1.getrec().getSize().x, stick1.getLocation().y };
	Point p2 = { stick1.getLocation().x, stick1.getLocation().y + stick1.getrec().getSize().y };
	Point q2 = { stick1.getLocation().x + stick1.getrec().getSize().x, stick1.getLocation().y + stick1.getrec().getSize().y };

	Point p3 = { stick2.getLocation().x, stick2.getLocation().y };
	Point q3 = { stick2.getLocation().x + stick2.getrec().getSize().x, stick2.getLocation().y };
	Point p4 = { stick2.getLocation().x, stick2.getLocation().y + stick2.getrec().getSize().y };
	Point q4 = { stick2.getLocation().x + stick2.getrec().getSize().x, stick2.getLocation().y + stick2.getrec().getSize().y };

	return doIntersect(p1, q1, p3, q3) || doIntersect(p1, q1, p4, q4) || doIntersect(p2, q2, p3, q3) || doIntersect(p2, q2, p4, q4);
}


void Stick::addOverLapped(const std::shared_ptr<Stick> &overlap)
{
	m_overlapped.push_back(overlap);
}

bool Stick::isLocationInside(const sf::Vector2f& location) const
{
	return m_stick.getGlobalBounds().contains(location);
}

bool Stick::isEraseable() const
{
	for (const auto& overlappedStick : m_overlapped)
	{
		if (overlappedStick->getIndex() > this->getIndex())
		{
			return false;
		}
	}
	return true;
}


	



