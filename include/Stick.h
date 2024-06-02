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
    ~Stick();
    
    sf::RectangleShape& getrec() const;
    const int getIndex() const;
    const sf::Color getColor() const;
    const sf::Vector2f getLocation() const;


    static bool isOverlaped(const sf::RectangleShape& rec1, const sf::RectangleShape& rec2);

    //static bool isOverlaped(const Stick& stick1, const Stick& stick2);
    void checkAvailableStick(const std::vector<std::shared_ptr<Stick>>& sticks, int numOfSticks);
    void addOverLapped(const std::shared_ptr<Stick>& overlap);
    int getOverLappedSize();
    bool isLocationInside(const sf::Vector2f& location) const;
    bool isEraseable() const;


private:
    std::vector<std::shared_ptr <Stick>> m_overlapped;
    std::vector<std::shared_ptr <Stick>> m_available;

    sf::RectangleShape m_stick;
    int m_index;
    sf::Vector2f m_location;
    sf::FloatRect m_bounds;
    Point m_points[2];

    void setColor(const Colors);

    int min(int a, int b) const;
    int max(int a, int b) const;
    bool onSegment(Point p, Point q, Point r) const;
    int orientation(Point p, Point q, Point r) const;
    bool doIntersect(Point p1, Point q1, Point p2, Point q2) const;

    Point getPoint(int index) const;
    Point getEndPoint(const Point& startP, int length, int degree) const;
};

