#pragma once

#include <SFML/Graphics.hpp>
#include <Resources.h>
#include <random> 
#include <iostream>

class Stick
{
public:
	Stick(const int row, const int length);
    sf::RectangleShape& getrec();
    const int getIndex() const;
    const sf::Color getColor() const;
    const sf::Vector2f getLocation() const;
    void setColor(const Colors);
    static bool isOverlaped(const Stick& stick1, const Stick& stick2);

    void addOverLapped(const std::shared_ptr<Stick>& overlap);

    bool isLocationInside(const sf::Vector2f& location) const;
 



private:
    std::vector<std::shared_ptr <Stick>> m_overlapped;
    sf::RectangleShape m_stick;
    int m_index;
    sf::Vector2f m_location;
    sf::FloatRect m_bounds;
    void setBounds(float x, float y, float STICK_WIDTH, float length);


};