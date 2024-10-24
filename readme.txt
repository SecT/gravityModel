////////How to set up the project//////////////////////////

1) Clone the repositiory
git clone git@github.com:SecT/gravityModel.git

2) Download SFML

The project has been tested with SFML version 2.5.1

The SFML folder with the following structure should be placed in the top repo folder (the one with CMakeLists.txt and main.cpp). 
The project structure should look like this:

gravityModel
|-CMakeLists.txt
|-main.cpp
...
|-SFML
	|--bin
	|--doc
	|--examples
	|--include
	|--lib

3) Run cmake to create a build env

cmake -S . -B [build folder for cmake]
e.g
cmake -S . -B myBuild
This will create myBuild directory with the generated cmake files

4) Build the project 

cmake --build [cmake build folder created in step 3]
e.g
cmake --build ./myBuild

5) Run the program

WIN:
	[cmake build folder created in step 3]\Debug\gravityModel.exe
	e.g
	.\myBuild\Debug\gravityModel.exe

LINUX:
	./myBuild/gravityModel

6) Run tests
[cmake build folder created in step 3]\myTests\Debug\myTests.exe
e.g
WIN:
	.\myBuildWin\myTests\Debug\myTests.exe
LINUX:
	./myBuild/myTests/myTests

////////Using the program//////////////////////////

Use the config.txt file for the input

The first line is dt - the time step

The second line is debugMode
In debugMode the simulation is only running when the space key is pressed
0 - debugMode off
1 - debugMode on

The third line is the sample configuration for the bodies.
Several sample configurations are available, specified in the txt files like example_ThreeBodies_Triangle.txt
By setting this line you choose which config should be loaded
0 - no config
1 - example_TwoBodies_SameX.txt        - two bodies, same mass, placed vertically, no initial velocity
2 - example_TwoBodies_SameX_InitV.txt  - two bodies, one mass is larger than the other, placed vertically, one body has got initial velocity
3 - example_TwoBodies_SameY.txt        - two bodies, same mass, placed horizontally, no initial velocity
4 - example_ThreeBodies_Triangle.txt   - three bodies, same mass, placed in the corners of a triangle, no initial velocity

