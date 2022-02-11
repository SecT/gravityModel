//int fun();

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

    float v_x;
    float v_y;

    Body(float r) : v_x(0.f), v_y(0.f)
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

    //TODO: just make Body drawable, instead of exposing myCircle
    sf::CircleShape getCircleShape()
    {
        return myCircle;
    }

};
