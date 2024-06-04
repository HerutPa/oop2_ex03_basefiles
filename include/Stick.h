#pragma once
#include <SFML/Graphics.hpp>
#include <Resources.h>
#include <algorithm> // For std::max and std::min
#include <iostream>
#include <string_view>
#include <complex>
#include <numeric>
#include <memory>
#include <vector>
#include <random>
#include <math.h>
#include <cmath>

struct Point
{
    int x;
    int y;
};


class Stick
{
public:
    Stick();
    Stick(int colorIndex, int score, int index, int positionX, int positionY, int rotation);
    Stick(const int row, const int length);

    std::string getStickData();
    
    const sf::RectangleShape& getShape() const;
    const sf::Vector2f getLocation() const;
    const int getIndex() const;
    void addOverLapped(const std::shared_ptr<Stick>& overlap);
    void setColor(const sf::Color& color);
    void deleteOverLapped();
    void resetColor();
  
    static bool isOverlaped(const sf::RectangleShape& rec1, const sf::RectangleShape& rec2);
    bool isLocationInside(const sf::Vector2f& location) const;
    bool isEraseable() const;
    bool checkAvailableStick() const;
    int getColorIndex() const { return m_colorIndex; }
    int returnScore() const;

    sf::RectangleShape& getrec() const;
    const std::vector<std::shared_ptr<Stick>>& getOverLapped() const;

private:
    Point getEndPoint(const Point& startP, int length, int degree) const;
    Point getPoint(int index) const;
    Point m_points[2];

    std::vector<std::shared_ptr <Stick>> m_overlapped;

    sf::RectangleShape m_stick;
    sf::Vector2f m_location;
    sf::FloatRect m_bounds;
    sf::Color m_currentColor;
    sf::Color m_color1 = sf::Color::Red;
    sf::Color m_color2 = sf::Color::Transparent;
   
    int orientation(Point p, Point q, Point r) const;
    int min(int a, int b) const;
    int max(int a, int b) const;
    int m_colorIndex;
    int m_score = 0;
    int m_index;
    int m_positionX;
    int m_positionY;
    int m_rotation;

    bool doIntersect(Point p1, Point q1, Point p2, Point q2) const;
    bool onSegment(Point p, Point q, Point r) const;

};

