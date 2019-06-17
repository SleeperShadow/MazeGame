# CMakeList.txt : CMake project for MazeGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project(MazeGame)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(SDL2_PATH "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2-2.0.9/")
	
set(SDL2_INCLUDE_DIR "${SDL2_PATH}/include")
set(SDL2_LIBRARY "${SDL2_PATH}/lib/x64/SDL2main.lib" "${SDL2_PATH}/lib/x64/SDL2.lib")
set(SDL2_DLL "${SDL2_PATH}/lib/x64/SDL2.dll")


include_directories(${SDL2_INCLUDE_DIR})
link_directories("${SDL2_LIBRARY}")	
file(COPY ${SDL2_DLL}
    DESTINATION ${PROJECT_BINARY_DIR})

set(SOURCE_FILES 
	"MazeGame.cpp"
	"MazeGame.h"
	"sources/Game.cpp"
	"sources/Game.h")
add_executable(MazeGame ${SOURCE_FILES})

target_link_libraries(MazeGame PRIVATE ${SDL2_LIBRARY} -lpthread)