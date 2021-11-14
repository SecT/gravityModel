cmake_minimum_required(VERSION 3.10)

# set the project name
project(myCmakeTraining VERSION 0.1)

# specify the C++ standard
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#config file is added to the include directory
#the first filename given is the base file, used to generate the second file
configure_file(myConfig.h.in myConfig.h)

add_subdirectory(myLib)

# add the executable
# this will be the output exe name
# The exe name doesn't need to be the same as the project name
add_executable(myCmakeTraining main.cpp)

target_link_libraries(myCmakeTraining PUBLIC myLib)

#this specifies the include directories. So the paths to included files in the source files don't need to be specified - the name is enough
target_include_directories(myCmakeTraining PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/myLib"
                           )