#include<iostream>
#include <cstdlib>
#include <set>
#include <string>
#include <iterator>
#include <tuple>

#include "myConfig.h"
#include "myLib.h"

#include "main.h"

#include <SFML/Window.hpp>

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

	sf::Window window(sf::VideoMode(800, 600), "My window");

	while (window.isOpen())
		{
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					window.close();
			}
		}

}