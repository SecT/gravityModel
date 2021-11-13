cmake_minimum_required(VERSION 3.10)

# set the project name
project(myCmakeTraining VERSION 0.1)

configure_file(myConfig.h.in myConfig.h)

# add the executable
# this will be the output exe name
# The exe name doesn't need to be the same as the project name
add_executable(myCmakeTraining main.cpp)

target_include_directories(myCmakeTraining PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )