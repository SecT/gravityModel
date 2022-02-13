#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Body : public sf::Drawable
{
private:

    sf::CircleShape myCircle;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(myCircle, states);
    }

public:
    float x;
    float y;
    float r;
    float m;

    float v_x;
    float v_y;

    float a_x;
    float a_y;

    Body( float rad, float newMass=1.0f) : x(0), y(0), r(rad), m(newMass), v_x(0.f), v_y(0.f), a_x(0.0f), a_y(0.0f)
    {
        myCircle = sf::CircleShape(r);
        myCircle.setFillColor(sf::Color(100, 250, 50));
    }

    void setPosition(float newX, float newY)
    {
        x = newX;
        y = newY;
        myCircle.setPosition(x, y);
    }

    void setVelocity(float newVx, float newVy)
    {
        v_x = newVx;
        v_y = newVy;
    }

    //TODO: no longer needed, Body is now drawable, so we don't need to expose the shape object
    sf::CircleShape getCircleShape()
    {
        return myCircle;
    }

};
