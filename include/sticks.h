#pragma once

#include <SFML/Graphics.hpp>
#include <Resources.h>
#include <random> 

class Sticks
{
public:
	Sticks(const int, const int);
	sf::CircleShape& get();
	const int getRow() const;
	const int getCol() const;
	const sf::Color getColor()const;
	const int getIndex()const;
	void setColor(const Colors color);
	//const sf::Vector2f Sticks::getPosition()const;
	//void setColor(const Colors);


private:
	sf::CircleShape m_stick;
	int m_col;
	int m_row;
};