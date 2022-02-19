#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <array>
#include <fstream>
#include <string>
#include <iomanip>
#include <iterator>
#include <iostream>
#include <math.h>

#include "Body.h"

using std::ifstream;
//using std::cerr;
using std::cout;
using std::endl;
using std::setw;
using std::vector;

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

void showOutput(vector<Body>& bodies)
{

    int columnWidth=16;

    cout<<endl;

    std::array<std::string, 7> headers = { { "Mass", "X", "Y", "Vx", "Vy", "Ax", "Ay" }};

    std::cout<<setw(4)<<headers[0];

    for (int i = 1; i < headers.size(); i++)
    {
        std::cout<<setw(columnWidth)<<headers[i];
    }

    std::cout<<endl;

    for(vector<Body>::iterator it = bodies.begin(); it != bodies.end(); ++it)
    {
        cout<<setw(4)<<(*it).m<<setw(columnWidth)<<(*it).x<<
            setw(columnWidth)<<(*it).y<<setw(columnWidth)<<(*it).v_x
            <<setw(columnWidth)
            <<(*it).v_y<<setw(columnWidth)<<(*it).a_x
            <<setw(columnWidth)<<(*it).a_y<<endl;
    }
}


void processMotionForBodies(vector<Body> &bodies, float dt)
{
    //TODO: refactoring and optimization
    //- F(A,B) = F(B,A) , where A,B - bodies
    //- ...

    vector<float> accelerations_x;
    vector<float> accelerations_y;

    for(vector<Body>::iterator it = bodies.begin(); it != bodies.end(); ++it)
    {

        //calculate accelaration
        //a = F/m
        //m can be normalized to 1
        float f_x = 0.f;
        float f_y = 0.f;
        for(vector<Body>::iterator jt = bodies.begin(); jt != bodies.end(); ++jt)
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

        float a_x = 0.0f;
        float a_y = 0.0f;

//        if((*it).m == 1)
//        {
//            //mass is 1, we can avoid costly division
//            a_x = f_x;
//            a_y = f_y;
//        }
//        else
        {
            a_x = f_x/(*it).m;
            a_y = f_y/(*it).m;
        }

        accelerations_x.push_back(a_x);
        accelerations_y.push_back(a_y);

        (*it).a_x = a_x;
        (*it).a_y = a_y;

    }

    for(vector<Body>::iterator it = bodies.begin(); it != bodies.end(); ++it)
    {

        //update velocity
        //v = v_old + a*t
        //t can be normalized to 1 ?
        //(*it).v_x+=a_x;
        //float dt = 1.f;
        (*it).v_x+=( (*it).a_x *dt);
        //(*it).v_y+=a_y;
        (*it).v_y+=( (*it).a_y *dt);

        //update position
        //x_current = x_old + v*t
        //t can be normalized to 1 ?
        (*it).setPosition((*it).x + (*it).v_x, (*it).y + (*it).v_y);
    }
}


void setupExampleConfig(vector<Body>& bodies, vector<float>& exampleConfig)
{
    const int numberOfParametersForBody = 6;
    int bodyCount = static_cast<int>(exampleConfig.size())/numberOfParametersForBody;

    for(int i = 0 ; i< bodyCount; i++)
    {
        bodies.push_back(Body(exampleConfig[1+i*numberOfParametersForBody], exampleConfig[i*numberOfParametersForBody]));
        bodies[i].setPosition(exampleConfig[2+i*numberOfParametersForBody],exampleConfig[3+i*numberOfParametersForBody]);
        bodies[i].setVelocity(exampleConfig[4+i*numberOfParametersForBody],exampleConfig[5+i*numberOfParametersForBody]);
    }
}


#endif
