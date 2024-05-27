#pragma once

#include <SFML/Graphics.hpp>
#include <Resources.h>
#include <random> 

class Sticks
{
public:
	Sticks(const int row, const int col, const int length);
    sf::RectangleShape& get();
    const int getRow() const;
    const int getCol() const;
    const sf::Color getColor() const;
    const int getIndex() const;
    //void setColor(const sf::Color color);
    const sf::Vector2f getPosition() const;
    void setColor(const Colors);


private:
    sf::RectangleShape m_stick;
    int m_col;
    int m_row;
};