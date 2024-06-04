#pragma once

#include <SFML/Graphics.hpp>
#include <Resources.h>
#include <random> 
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm> // For std::max and std::min
#include <cmath>
#include <math.h>
#include <complex>
#include <numeric>
#include <string_view>


struct Point
{
    int x;
    int y;
};


class Stick
{
public:
    Stick();
    Stick(const int row, const int length);
    
    sf::RectangleShape& getrec() const;
    const int getIndex() const;
    const sf::Color getColor() const;
    const sf::Vector2f getLocation() const;
    static bool isOverlaped(const sf::RectangleShape& rec1, const sf::RectangleShape& rec2);
    void addOverLapped(const std::shared_ptr<Stick>& overlap);
    void hintColorsChange();
    void deleteOverLapped();
    bool isLocationInside(const sf::Vector2f& location) const;
    bool isEraseable() const;
    bool checkAvailableStick() const;
    int getOverLappedSize();



private:
    std::vector<std::shared_ptr <Stick>> m_overlapped;
    sf::RectangleShape m_stick;
    sf::Vector2f m_location;
    sf::FloatRect m_bounds;
    Point m_points[2];
    int m_index;

    bool m_isColor1 = true;
    sf::Color m_currentColor;
    sf::Color m_color1 = sf::Color::Red;
    sf::Color m_color2 = sf::Color::Transparent;

    void setColor(const Colors);
    int min(int a, int b) const;
    int max(int a, int b) const;
    int orientation(Point p, Point q, Point r) const;
    bool onSegment(Point p, Point q, Point r) const;
    bool doIntersect(Point p1, Point q1, Point p2, Point q2) const;

    Point getPoint(int index) const;
    Point getEndPoint(const Point& startP, int length, int degree) const;
};

