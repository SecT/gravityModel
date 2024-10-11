
#include <fstream>
#include <nlohmann/json.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <cstdlib>

#include "myConfig.h"
#include "Body.h"
#include "myLib.h"

#include "main.h"

using std::cout;
using std::endl;
using std::vector;


int main()
{
    cout<<"Gravity Model"<<endl;
    cout<<"Version: ";
    cout<<Tutorial_VERSION_MAJOR << "."<< Tutorial_VERSION_MINOR <<endl;

    float dt = 1.f;
    bool debugMode = false;               //process motion only when space key is pressed
    int exampleUsed = 4;

    int window_width = 800;
    int window_height = 600;

    //read from the old config file
    //vector<float> config;
    //readFromFile(config, "config.txt");
    //dt = config[0];
    //debugMode = config[1];
    //exampleUsed = static_cast<int>(config[2]);
    /////////



	// read configuration from the json file 	
	std::ifstream configFile("config.json");
	if (!configFile.fail())
	{
		nlohmann::json myConfig = nlohmann::json::parse(configFile);
		
		
		dt            = myConfig["dt"];
		//debugMode     = myConfig["debugMode"];
		//cout<<myConfig["debugMode"]<<endl;
		debugMode = myConfig["debugMode"] == 1 ? true : false ;
		exampleUsed   = static_cast<int>(myConfig["exampleUsed"]);
		window_width  = myConfig["window_width"];
		window_height = myConfig["window_height"];
	}
	////

    cout<<"dt: "                   <<dt<<endl;
    cout<<"DebugMode: "            <<debugMode<<endl;
    cout<<"Using example setting: "<<exampleUsed<<endl;
    cout<<"window_width: "         <<window_width<<endl;
    cout<<"window_height: "        <<window_height<<endl;


    //sf::Window window(sf::VideoMode(800, 600), "My window");
    sf::RenderWindow  window(sf::VideoMode(window_width, window_height), "Gravity Model");

    vector<Body> bodies;
    //bodies.push_back(Body(25.f));

    vector<float> exampleConfig;
    //Configuration
    switch(exampleUsed)
    {
    case 0:
        break;
    case 1:
        //setupExample_TwoBodiesSameX(bodies);

        readFromFile(exampleConfig, "example_TwoBodies_SameX.txt");
        setupExampleConfig(bodies, exampleConfig);
        break;
    case 2:
        //setupExample_TwoBodiesSameXInitialVelocity(bodies);
        readFromFile(exampleConfig, "example_TwoBodies_SameX_InitV.txt");
        setupExampleConfig(bodies, exampleConfig);
        break;
    case 3:
        //setupExample_TwoBodiesSameY(bodies);
        readFromFile(exampleConfig, "example_TwoBodies_SameY.txt");
        setupExampleConfig(bodies, exampleConfig);
        break;
    case 4:
        //setupExample_ThreeBodiesTriangle(bodies);
        readFromFile(exampleConfig, "example_ThreeBodies_Triangle.txt");
        setupExampleConfig(bodies, exampleConfig);
        break;
    default:
        break;
    }

    cout<<"Sfml start"<<endl;

    while (window.isOpen())
    {
        //cout<<"Event"<<endl;

        //process motion without an input from the user
        if(!debugMode)
        {
            processMotionForBodies(bodies, dt);
            showOutput(bodies);
        }

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ) )
            {
                window.close();
            }

            //process motion only when key is pressed
            if(debugMode)
            {

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        processMotionForBodies(bodies, dt);
                        showOutput(bodies);
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        for (vector<Body>::iterator it = bodies.begin(); it != bodies.end(); ++it)
        {
            window.draw((*it));
        }


        // end the current frame
        window.display();

    }

    return 0;
}
