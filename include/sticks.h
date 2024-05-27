#pragma once

#include <SFML/Graphics.hpp>
#include <Resources.h>
#include <random> 

class Sticks
{
public:
	Sticks(const int row, const int length);
    sf::RectangleShape& get();
    const int getRow() const;
    const sf::Color getColor() const;
    const sf::Vector2f getPosition() const;
    void setColor(const Colors);
    static bool isOverlaped(const Sticks& stick1, const Sticks& stick2);


private:
    std::vector<std::shared_ptr <Sticks>> m_overlapped;
    sf::RectangleShape m_stick;
    int m_row;

};