
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <iterator>
#include <iostream>
#include <math.h>

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

    }

    int i=0;

    int numberOfSpacesForFormattingOutput=15;

    cout<<"Mass               X               Y              Vx              Vy              Ax              Ay"<<endl;

    for(vector<Body>::iterator it = bodies.begin(); it != bodies.end(); ++it)
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


        cout<<setw(4)<<(*it).m<<" "<<setw(numberOfSpacesForFormattingOutput)<<(*it).x<<" "
            <<setw(numberOfSpacesForFormattingOutput)<<(*it).y<<" "<<setw(numberOfSpacesForFormattingOutput)<<(*it).v_x<<" "
            <<setw(numberOfSpacesForFormattingOutput)
            <<(*it).v_y<<" "<<setw(numberOfSpacesForFormattingOutput)<<accelerations_x[i]<<" "
            <<setw(numberOfSpacesForFormattingOutput)<<accelerations_y[i]<<endl;

        i++;
    }

}

void setupExample_TwoBodiesSameX(vector<Body>& bodies)
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

void setupExample_TwoBodiesSameXInitialVelocity(vector<Body>& bodies)
{
    //Test case - two bodies on the same X, one has got initial velocity, the other has got larger mass
    bodies.push_back(Body(35.f, 3.0f));
    bodies.push_back(Body(25.f));
    bodies[0].setPosition(400, 300);
    bodies[1].setPosition(400, 200);
    bodies[0].setVelocity(0.f, 0.f);
    bodies[1].setVelocity(1.0f, 0.f);
    ///
}

void setupExample_TwoBodiesSameY(vector<Body>& bodies)
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

void setupExample_ThreeBodiesTriangle(vector<Body>& bodies)
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
