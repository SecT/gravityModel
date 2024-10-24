cmake_minimum_required(VERSION 3.10)

# set the project name
project(gravityModel VERSION 0.1)

# specify the C++ standard
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#config file is added to the include directory
#the first filename given is the base file, used to generate the second file
configure_file(myConfig.h.in myConfig.h)

add_subdirectory(Body)
add_subdirectory(myLib)

add_subdirectory(myTests)

#add_subdirectory("SFML-2.5.1/lib/cmake")

include(FetchContent)

##json
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
####

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



#required to run tests by the "ctest" command
enable_testing()

# add the executable
# this will be the output exe name
# The exe name doesn't need to be the same as the project name
add_executable(gravityModel main.cpp)
#add_executable(myTests myTests.cpp)

#add_library( sfml-window SHARED IMPORTED )

#link_directories("${PROJECT_SOURCE_DIR}/SFML-2.5.1/lib")




#this specifies the include directories. So the paths to included files in the source files don't need to be specified - the name is enough
target_include_directories(gravityModel PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/myLib"
                           "${PROJECT_SOURCE_DIR}/Body"
                           "${PROJECT_SOURCE_DIR}/SFML/include/"
                           "${PROJECT_SOURCE_DIR}/SFML/bin"
#                           "${PROJECT_SOURCE_DIR}/SFML-2.5.1/lib"
                           )

#target_link_directories(gravityModel PUBLIC "${PROJECT_SOURCE_DIR}/SFML-2.5.1/lib")

#target_link_libraries(gravityModel PUBLIC Body)

IF (UNIX)
	target_link_libraries(gravityModel PUBLIC -lsfml-window -lsfml-graphics -lsfml-system)
ENDIF (UNIX)

IF(WIN32)
	target_link_libraries(gravityModel PUBLIC Body "${PROJECT_SOURCE_DIR}/SFML/lib/sfml-system.lib" "${PROJECT_SOURCE_DIR}/SFML/lib/sfml-window.lib" "${PROJECT_SOURCE_DIR}/SFML/lib/sfml-graphics.lib")
ENDIF(WIN32)

target_link_libraries(gravityModel PRIVATE nlohmann_json::nlohmann_json)

#target_link_libraries(myTests PUBLIC gtest_main Body)

#copy dlls needed for runtime to the exe dir
IF(WIN32)
	add_custom_command(TARGET gravityModel POST_BUILD
    	COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/SFML/bin/sfml-window-2.dll" "${PROJECT_BINARY_DIR}/Debug/"
    	COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/SFML/bin/sfml-window-d-2.dll" "${PROJECT_BINARY_DIR}/Debug/"
    	COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/SFML/bin/sfml-system-2.dll" "${PROJECT_BINARY_DIR}/Debug/"
    	COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/SFML/bin/sfml-system-d-2.dll" "${PROJECT_BINARY_DIR}/Debug/"
    	COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/SFML/bin/sfml-graphics-2.dll" "${PROJECT_BINARY_DIR}/Debug/"
    	COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/SFML/bin/sfml-graphics-d-2.dll" "${PROJECT_BINARY_DIR}/Debug/"
    	)
ENDIF(WIN32)

#target_include_directories( myTests PUBLIC
#                           "${PROJECT_SOURCE_DIR}/Body"
#)

#required to run tests by the "ctest" command
#include(GoogleTest)
#gtest_discover_tests(myTests)
