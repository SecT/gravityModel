#include<iostream>
#include <cstdlib>
//#include <set>
#include<vector>
#include <string>
#include <iterator>
//#include <tuple>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <math.h>

#include "myConfig.h"
#include "myLib.h"

#include "main.h"

float calculateDistance_x(Body& b1, Body& b2)
{
    float dist = 1.0f;

//    dist = sqrt( (b2.x-b1.x)*(b2.x-b1.x) + (b2.y-b1.y)*(b2.y-b1.y) );
    //dist = abs( (b2.x-b1.x) );
    dist = ( (b2.x-b1.x) );



    return dist;
}

float calculateDistance_y(Body& b1, Body& b2)
{
    float dist = 1.0f;

//    dist = sqrt( (b2.x-b1.x)*(b2.x-b1.x) + (b2.y-b1.y)*(b2.y-b1.y) );
    //dist = abs( (b2.y-b1.y) );
    dist = ( (b2.y-b1.y) );

    return dist;
}


void processMotionForBodies(std::vector<Body> &bodies, float dt)
{
    //TODO: refactoring and optimization
    //- F(A,B) = F(B,A) , where A,B - bodies
    //- ...

    std::vector<float> accelerations_x;
    std::vector<float> accelerations_y;



    for(std::vector<Body>::iterator it = bodies.begin(); it != bodies.end(); ++it)
    {

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

                const float G = 1;
                //calculate f_n between (it) and (jt)
                //then add f to the sum of forces on (it)
                //F=G*m1*m2/r^2
                //m1=m2=1

                float r_x = calculateDistance_x( (*jt), (*it) );
                float r_y = calculateDistance_y( (*jt), (*it) );
                float r_x_sqr = r_x*r_x;
                float r_y_sqr = r_y*r_y;

                //get the direction of the vector - gravity is a attractive force
                ///////////
                //TODO: remove ugly hack...
                if(((*jt).x-(*it).x) < 0 )
                {
                    r_x_sqr = -r_x_sqr;
                }

                //TODO: remove ugly hack...
                if(((*jt).y-(*it).y) < 0 )
                {
                    r_y_sqr = -r_y_sqr;
                }
                ////////////////

                if(r_x_sqr != 0)
                {
                    f_n_x = G/r_x_sqr;
                }
                else
                {
                    f_n_x = 0;
                }


                if(r_y_sqr != 0)
                {
                    f_n_y = G/r_y_sqr;
                }
                else
                {
                    f_n_y = 0;
                }


                f_x+=f_n_x;
                f_y+=f_n_y;
            }
        }
        //m=1
        float a_x = f_x;
        float a_y = f_y;

        accelerations_x.push_back(a_x);
        accelerations_y.push_back(a_y);

    }

    int i=0;
    for(std::vector<Body>::iterator it = bodies.begin(); it != bodies.end(); ++it)
    {


        //update velocity
        //v = v_old + a*t
        //t can be normalized to 1 ?
        //(*it).v_x+=a_x;
        //float dt = 1.f;
        (*it).v_x+=(accelerations_x[i] *dt);
        //(*it).v_y+=a_y;
        (*it).v_y+=(accelerations_y[i] *dt);

        //update position
        //x_current = x_old + v*t
        //t can be normalized to 1 ?
        (*it).setPosition((*it).x + (*it).v_x, (*it).y + (*it).v_y);


        std::cout<<(*it).x<<" "<<(*it).y<<std::endl;

        i++;
    }

}

void setupExample_TwoBodiesSameX(std::vector<Body>& bodies)
{
    //Test case - two bodies on the same X
    bodies.push_back(Body(25.f));
    bodies.push_back(Body(25.f));
    bodies[0].setPosition(400, 300);
    bodies[1].setPosition(400, 200);
    bodies[0].setVelocity(0.f, 0.f);
    bodies[1].setVelocity(0.f, 0.f);
    ///
}

void setupExample_TwoBodiesSameY(std::vector<Body>& bodies)
{
    //Test case - two bodies on the same Y
    bodies.push_back(Body(25.f));
    bodies.push_back(Body(25.f));
    bodies[0].setPosition(400, 300);
    bodies[1].setPosition(300, 300);
    bodies[0].setVelocity(0.f, 0.f);
    bodies[1].setVelocity(0.f, 0.f);
    //////
}

void setupExample_ThreeBodiesTriangle(std::vector<Body>& bodies)
{
    //Test case - three bodies placed in a triangle corners
    bodies.push_back(Body(25.f));
    bodies.push_back(Body(25.f));
    bodies.push_back(Body(25.f));
    bodies[0].setVelocity(0.f, 0.f);
    bodies[1].setVelocity(0.f, 0.f);
    bodies[2].setVelocity(0.f, 0.f);
    bodies[0].setPosition(400, 100);
    bodies[1].setPosition(200, 400);
    bodies[2].setPosition(600, 400);
    //////
}

int main()
{
    std::cout<<"Gravity Model"<<std::endl;
    std::cout<<"Version: ";
    std::cout<<Tutorial_VERSION_MAJOR << "."<< Tutorial_VERSION_MINOR <<std::endl;


    float dt = 1.f;
    std::cout<<"dt: "<<std::endl;

    int window_width = 800;
    int window_height = 600;

    //sf::Window window(sf::VideoMode(800, 600), "My window");
    sf::RenderWindow  window(sf::VideoMode(window_width, window_height), "Gravity Model");

    std::vector<Body> bodies;
    //bodies.push_back(Body(25.f));

    //Configuration
    setupExample_TwoBodiesSameX(bodies);
    //setupExample_TwoBodiesSameY(bodies);
    //setupExample_ThreeBodiesTriangle(bodies);

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

                    processMotionForBodies(bodies, dt);
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
