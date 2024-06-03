#include "Stick.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Stick::Stick()
{
} 

Stick::Stick(const int row, const int length)
{
    m_index = row;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution_x(0.f, 90.f);
    std::uniform_int_distribution<int> distribution_y(0.f, 9.f);
    int x = 300 + distribution_x(generator) * STICK_WIDTH;
    int y = 100 + distribution_y(generator) * STICK_LENGTH;
    std::uniform_int_distribution<int> distribution2(0, 5);
    int randomNumColor = distribution2(generator);
    std::uniform_int_distribution<int> distribution3(10.f, 355.f);
    int randomNumAngel = distribution3(generator);

    m_stick.setSize(sf::Vector2f(length, 150));
    m_stick.setOrigin(25, 25);
    m_stick.setPosition(x, y);
    m_stick.setRotation(randomNumAngel);
    m_stick.setFillColor(Resources::instance().getColorArray()[randomNumColor]);
    m_stick.setOutlineThickness(OUTLINE);
    m_stick.setOutlineColor(sf::Color::Black);
    m_location.x = x;
    m_location.y = y;
    
    m_points[0].x = x;
    m_points[0].y = y;
    m_points[1] = getEndPoint(m_points[0], length, randomNumAngel);
}


Point Stick::getEndPoint(const Point& startP, int length, int degree) const
{
    // convert angle from degrees to radians
    double angleRad = degree * M_PI / 180.0;

    // calculate coordinates
    double new_x = startP.x + length * cos(angleRad);
    double new_y = startP.y + length * sin(angleRad);

    return { static_cast<int>(new_x), static_cast<int>(new_y) };
}


inline float dotProduct(const sf::Vector2f& vertex, const sf::Vector2f& axis)
{
    return vertex.x * axis.x + vertex.y * axis.y;
}

void Stick::deleteOverLapped()
{
    for (const auto& overlappedStick : m_overlapped)
    {
        int index = this->getIndex();
        overlappedStick->m_overlapped.erase(std::remove_if(overlappedStick->m_overlapped.begin(), overlappedStick->m_overlapped.end(),
            [index](const std::shared_ptr<Stick>& stick) { return stick->getIndex() == index; }),
            overlappedStick->m_overlapped.end());
    }

}

bool Stick::isOverlaped(const sf::RectangleShape& rec1, const sf::RectangleShape& rec2)
{
    auto getVertices = [](const sf::RectangleShape& rec)
        {
        sf::Transform transform = rec.getTransform();
        sf::FloatRect rect = rec.getLocalBounds();
        return std::vector<sf::Vector2f>
        {
            transform.transformPoint(sf::Vector2f(rect.left, rect.top)),
                transform.transformPoint(sf::Vector2f(rect.left + rect.width, rect.top)),
                transform.transformPoint(sf::Vector2f(rect.left + rect.width, rect.top + rect.height)),
                transform.transformPoint(sf::Vector2f(rect.left, rect.top + rect.height))
        };
        };

    std::vector<sf::Vector2f> vertices1 = getVertices(rec1);
    std::vector<sf::Vector2f> vertices2 = getVertices(rec2);

    std::vector<sf::Vector2f> axes{
        vertices1[1] - vertices1[0], vertices1[2] - vertices1[1],
        vertices2[1] - vertices2[0], vertices2[2] - vertices2[1]
    };

    for (const auto& axis : axes)
    {
        float minProjection1 = std::numeric_limits<float>::max();
        float maxProjection1 = std::numeric_limits<float>::lowest();
        for (const auto& vertex : vertices1)
        {
            float projection = dotProduct(vertex, axis);
            minProjection1 = std::min(minProjection1, projection);
            maxProjection1 = std::max(maxProjection1, projection);
        }

        float minProjection2 = std::numeric_limits<float>::max();
        float maxProjection2 = std::numeric_limits<float>::lowest();
        for (const auto& vertex : vertices2)
        {
            float projection = dotProduct(vertex, axis);
            minProjection2 = std::min(minProjection2, projection);
            maxProjection2 = std::max(maxProjection2, projection);
        }

        if (maxProjection1 < minProjection2 || maxProjection2 < minProjection1)
        {
            return false; // Separating axis found
        }
    }
    return true; // No separating axis found
}


//Available sticks vector update
bool Stick::checkAvailableStick() const
{
    if (this->m_overlapped.empty())
    {
        return true;
    }
    else
    {
        for (const auto& stickCur : m_overlapped)
        {
            int notAbove = 0;
            for (const auto& overlappedStick : stickCur->m_overlapped)
            {
                int this_index = getIndex();
                int ovlap = overlappedStick->getIndex(); 
                if (getIndex() > overlappedStick->getIndex())
                {
                    notAbove++;
                }
            }
            if (notAbove == stickCur->m_overlapped.size())
            {
                return true;
            }
        }
    }
    return false; 
}


//void Stick::hintColorsChange()
//{
//
//}

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

// min and max functions
int Stick::min(int a, int b) const
{
    return (a < b) ? a : b;
}


int Stick::max(int a, int b) const
{
    return (a > b) ? a : b;
}


void Stick::addOverLapped(const std::shared_ptr<Stick>& overlap)
{
    m_overlapped.push_back(overlap);
    std::cout << m_index << " ";
}


// Given three collinear points p, q, r, the function checks if 
// pointq lies on line segment 'pr' 
bool Stick::onSegment(Point p, Point q, Point r) const
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;

    return false;
}

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are collinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int Stick::orientation(Point p, Point q, Point r) const
{
    int val = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool Stick::doIntersect(Point p1, Point q1, Point p2, Point q2) const
{
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case 
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases 
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases 
}


Point Stick::getPoint(int index) const
{
    if (index != 0 && index != 1)
    {
        std::cout << "bad index for Stick::getPoint()\n";
        exit(EXIT_FAILURE);
    }
    return { m_points[index].x , m_points[index].y };
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


bool Stick::isLocationInside(const sf::Vector2f& location) const
{
    return m_stick.getLocalBounds().contains(m_stick.getInverseTransform().transformPoint(location));
}




