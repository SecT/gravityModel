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


void processMotionForBodies(std::vector<Body> &bodies)
{

    for(std::vector<Body>::iterator it = bodies.begin(); it != bodies.end(); ++it)
    {

        //calculate

        //calculate accelaration
        //a = F/m
        //m can be normalized to 1
        float f_x = 0.f;
        float f_y = 0.f;
        for(std::vector<Body>::iterator jt = bodies.begin(); jt != bodies.end(); ++jt)
        {
            if( it != jt  )
            {
                float f_n_x = 0.f;
                float f_n_y = 0.f;
                //calculate f_n between (it) and (jt)
                //then add f to the sum of forces on (it)
                f_x+=f_n_x;
                f_y+=f_n_y;
            }
        }
        //m=1
        float a_x = f_x;
        float a_y = f_y;

        //update velocity
        //v = v_old + a*t
        //t can be normalized to 1 ?
        (*it).v_x+=a_x;
        (*it).v_y+=a_y;

        //update position
        //x_current = x_old + v*t
        //t can be normalized to 1 ?
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
