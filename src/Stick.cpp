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

static bool doIntersect(Point p1, Point q1, Point p2, Point q2);
{
	// Find the four orientations needed for general and special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
	{
		return true;
	}

	// Special Cases
	// p1, q1, and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1))
	{
		return true;
	}
	// p1, q1, and q2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1))
	{
		return true;
	}
	// p2, q2, and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2))
	{
		return true;
	}
	// p2, q2, and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2))
	{
		return true;
	}

	// No special case applies
	return false;
}

bool Stick::onSegment(Point p, Point q, Point r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y)) {
		return true;
	}
	return false;
}

int Stick::orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0) {
		return 0;  // collinear
	}
	return (val > 0) ? 1 : 2; // clock or counterclockwise
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


	



