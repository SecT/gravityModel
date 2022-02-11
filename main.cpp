#include<iostream>
#include <cstdlib>
#include <set>
#include <string>
#include <iterator>
#include <tuple>


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "myConfig.h"
#include "myLib.h"

#include "main.h"



struct S {
    int n;
    std::string s;
    float d;
    bool operator<(const S& rhs) const
    {
        // compares n to rhs.n,
        // then s to rhs.s,
        // then d to rhs.d
        return std::tie(n, s, d) < std::tie(rhs.n, rhs.s, rhs.d);
    }
};


int fun()
{
	auto a = 1;
	
	return a;
}


int main()
{
	std::cout<<"Hello Cmake World"<<std::endl;
	std::cout<<myDef<<std::endl;
	std::cout<<"Version: ";
	std::cout<<Tutorial_VERSION_MAJOR << "."<< Tutorial_VERSION_MINOR <<std::endl;
	
	
	std::cout<<fun()<<std::endl;
	
	//from myLib.h
	std::cout<<fun2()<<std::endl;
	//

    // pre C++17:
    {
		std::set<S> mySet;
		
	    S value{42, "Test", 3.14};
	    std::set<S>::iterator iter;
	    bool inserted;

	    // unpacks the return val of insert into iter and inserted
	    std::tie(iter, inserted) = mySet.insert(value);

	    if (inserted)
		    std::cout << "Value was inserted\n";
    }

	// with C++17
	//this shows a warning (not an error?) when compiled with older cpp standard specified
    {
		std::set<S> mySet;
		
        S value{100, "abc", 100.0};
        const auto [iter, inserted] = mySet.insert(value);

        if (inserted)
		    std::cout << "Value(" << iter->n << ", " << iter->s << ", ...) was inserted" << "\n";
    }

	int window_width = 800;
	int window_height = 600;

	//sf::Window window(sf::VideoMode(800, 600), "My window");
	sf::RenderWindow  window(sf::VideoMode(window_width, window_height), "My window 2");

	sf::RectangleShape myRectangle(sf::Vector2f(200.f, 50.f));
	
	int rect_x = 300;
	int rect_y = 500;
	
	myRectangle.setFillColor(sf::Color(100, 250, 50));
	//myRectangle.setSize(sf::Vector2f(100.f, 100.f));
	myRectangle.setPosition(rect_x,rect_y);

	int circle_x = 400;
	int circle_y = 300;
	float circle_r = 25.f;

	//sf::Vector2f circle_movement(1.f, 0.f);
	sf::Vector2f circle_movement(1.f, 1.f);

	sf::CircleShape myCircle(circle_r);
	
	myCircle.setFillColor(sf::Color(100, 250, 50));

std::cout<<"Sfml start"<<std::endl;

	while (window.isOpen())
		{
			
			std::cout<<"Event"<<std::endl;
			
			myCircle.setPosition(circle_x,circle_y);
			
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (window.pollEvent(event))
			{
				
				std::cout<<"Event"<<std::endl;
				
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Left)
					{
						rect_x--;
						
						
						
						myRectangle.setPosition(rect_x,rect_y);
					}
					
					if (event.key.code == sf::Keyboard::Right)
					{
						rect_x++;
						
						myRectangle.setPosition(rect_x,rect_y);
					}
					
					std::cout<<"rect_x: "<<rect_x<<std::endl;
				}
			}
		
		window.clear(sf::Color::White);
		
		window.draw(myRectangle);
		window.draw(myCircle);
		
		// end the current frame
        window.display();
		
		if (circle_x+circle_r*2+circle_movement.x< window_width && circle_x+circle_movement.x>=0)
		{
			circle_x=circle_x+circle_movement.x;
		}
		else{
			//bounce the ball off the wall
			circle_movement.x = -circle_movement.x;
		}
		
		if (circle_y+circle_r*2+circle_movement.y< window_height && circle_y+circle_movement.y>=0)
		{
			circle_y=circle_y+circle_movement.y;
		}
		else{
			//bounce the ball off the wall
			circle_movement.y = -circle_movement.y;
		}
		
		}

	return 0;
}