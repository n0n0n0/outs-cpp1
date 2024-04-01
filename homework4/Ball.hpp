#pragma once
#include <istream>
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    void setColor(const Color& color);
    void setRadius(double radius);
private:
    Velocity    m_velocity;
    Point       m_center;
    double      m_radius;
    Color       m_color;
};
