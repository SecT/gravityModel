//int fun();

#include <vector>
#include <fstream>
//#include <iostream>
#include <string>

using std::ifstream;
//using std::cerr;
//using std::cout;
//using std::endl;
using std::vector;

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

    Body( float rad, float newMass=1.0f) : x(0), y(0), r(rad), v_x(0.f), v_y(0.f), m(newMass)
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


void readFromFile(vector<float>& config, std::string filename)
{
    ifstream indata; // indata is like cin
    float num; // variable for input value
    indata.open(filename); // opens the file
    if(!indata)   // file couldn't be opened
    {
        //cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    indata >> num;

    while ( !indata.eof() )   // keep reading until end-of-file
    {
        //cout << "The next number is " << num << endl;
        config.push_back(num);
        indata >> num; // sets EOF flag if no value found
    }
    indata.close();
    //cout << "End-of-file reached.." << endl;
}
