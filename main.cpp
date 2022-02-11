#include<iostream>
#include <cstdlib>
//#include <set>
#include<vector>
#include <string>
#include <iterator>
//#include <tuple>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "myConfig.h"
#include "myLib.h"

#include "main.h"


//struct S {
//    int n;
//    std::string s;
//    float d;
//    bool operator<(const S& rhs) const
//    {
//        // compares n to rhs.n,
//        // then s to rhs.s,
//        // then d to rhs.d
//        return std::tie(n, s, d) < std::tie(rhs.n, rhs.s, rhs.d);
//    }
//};
//
//int fun()
//{
//	auto a = 1;
//
//	return a;
//}

void processMotionForBodies(std::vector<Body> &bodies)
{

    for(std::vector<Body>::iterator it = bodies.begin(); it != bodies.end(); ++it)
    {
        (*it).setPosition((*it).x + (*it).v_x, (*it).y + (*it).v_y);
        std::cout<<(*it).x<<" "<<(*it).y<<std::endl;
    }

}


int main()
{
    std::cout<<"Gravity Model"<<std::endl;
    std::cout<<"Version: ";
    std::cout<<Tutorial_VERSION_MAJOR << "."<< Tutorial_VERSION_MINOR <<std::endl;


    int window_width = 800;
    int window_height = 600;

    //sf::Window window(sf::VideoMode(800, 600), "My window");
    sf::RenderWindow  window(sf::VideoMode(window_width, window_height), "Gravity Model");

    std::vector<Body> bodies;

    bodies.push_back(Body(55.f));
    bodies.push_back(Body(25.f));

    //sf::Vector2f circle_movement(1.f, 0.f);
    //sf::Vector2f circle_movement(1.f, 1.f);
    //body0.setVelocity(1.f, 0.f);
    bodies[0].setVelocity(1.f, 0.f);
    bodies[1].setVelocity(-1.f, 0.f);

    bodies[0].setPosition(400, 300);
    bodies[1].setPosition(400, 200);

    std::cout<<"Sfml start"<<std::endl;

    while (window.isOpen())
    {
        //std::cout<<"Event"<<std::endl;

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ) )
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    std::cout<<std::endl;

                    processMotionForBodies(bodies);
                }
            }
        }

        window.clear(sf::Color::White);

        for (std::vector<Body>::iterator it = bodies.begin(); it != bodies.end(); ++it)
        {
            window.draw((*it));
        }


        // end the current frame
        window.display();

    }

    return 0;
}
