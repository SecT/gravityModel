by GS

https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html


Cmake tutorials:
https://github.com/google/googletest
https://google.github.io/googletest/quickstart-cmake.html
https://cmake.org/cmake/help/v3.17/guide/tutorial/index.html

////////////Full commands for project conf, build and test/////////////////////////////
//cygwin
cmake -S . -B myBuild/ && cmake --build myBuild &&  cd myBuild/ && ctest && cd ..

//win
cmake -S . -B myBuildWin/ ; cmake --build myBuildWin ;  cd myBuildWin/ ; ctest ; cd ..11
/////////////////////////////////////////////////////////////////////////


//run cmake to configure project and build
//you only need to run it when any cmakelists.txt file was modified
//"build" is the target dir here, so e.g "cmake -S . -B myBuildCyg" can be used as a separate dir for cygwin. It may be useful to have separate dirs for various targets 
cmake -S . -B build

//Build the project
//"build" is the target dir here, so e.g "cmake --build myBuildCyg" can be used as a separate dir for cygwin. It may be useful to have separate dirs for various targets 
cmake --build build

//run the executable 
./build/test009.exe

/////////////run google tests
//method a) enter build dir, run tests and go back to main dir 
cd build && ctest && cd ..
Na windows / powershell:
cd .\build\ ; ctest ; cd ..

//method b)
//specify the test directory by parameter
ctest --test-dir build/ 
//////////////////

Check VS compiler version, powershell
PS F:\Projekty\test009> cd "C:/Program Files (x86)/Microsoft Visual Studio/2019/BuildTools/VC/Tools/MSVC/14.27.29110/bin/Hostx64/x64/"
PS C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.27.29110\bin\Hostx64\x64> .\cl.exe
Microsoft (R) C/C++ wersja kompilatora optymalizującego 19.27.29112 dla x64

grep -r "Visual Studio" ./build --color  // search the cmake build dir in makefiles for version? 