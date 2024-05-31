#include "Stick.h"

Stick::Stick(const int row, const int length) {
    m_index = row;
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_real_distribution<float> distribution_x(0.f, 90.f);
    std::uniform_real_distribution<float> distribution_y(0.f, 9.f);

    float x = 300 + distribution_x(generator) * STICK_WIDTH;
    float y = 100 + distribution_y(generator) * STICK_LENGTH;

    std::uniform_int_distribution<int> distribution2(0, 5);
    int randomNumColor = distribution2(generator);

    std::uniform_real_distribution<float> distribution3(10.f, 355.f);
    float randomNumAngel = distribution3(generator);

    m_stick.setSize(sf::Vector2f(length, 150));
    m_stick.setOrigin(25, 25);
    m_stick.setPosition(x, y);
    m_stick.setRotation(randomNumAngel);
    m_stick.setFillColor(Resources::instance().getColorArray()[randomNumColor]);
    m_stick.setOutlineThickness(OUTLINE);
    m_stick.setOutlineColor(sf::Color::Black);
    m_location.x = x;
    m_location.y = y;
}

sf::RectangleShape& Stick::getrec() const {
    return const_cast<sf::RectangleShape&>(m_stick);
}

const int Stick::getIndex() const {
    return m_index;
}

const sf::Color Stick::getColor() const {
    return m_stick.getFillColor();
}

const sf::Vector2f Stick::getLocation() const {
    return m_location;
}

void Stick::setColor(const Colors color) {
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



int Stick::orientation(Point p, Point q, Point r)
{
    float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1 : 2;  // clock or counterclock wise
}

bool Stick::doIntersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    std::cout << "here" ;

    return false;
}

bool Stick::onSegment(Point p, Point q, Point r)
{
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) && q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
        return true;
    return false;
}








void Stick::addOverLapped(const std::shared_ptr<Stick>& overlap)
{
    m_overlapped.push_back(overlap);
    std::cout << m_index << " ";
}

bool Stick::isLocationInside(const sf::Vector2f& location) const
{
    return m_stick.getLocalBounds().contains(m_stick.getInverseTransform().transformPoint(location));
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