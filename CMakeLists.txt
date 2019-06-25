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

set(SDL2_IMAGE_PATH "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2_image-2.0.4")
set(SDL2_IMAGE_INCLUDE_DIR "${SDL2_IMAGE_PATH}/include")
set(SDL2_IMAGE_LIBRARY "${SDL2_IMAGE_PATH}/lib/x64/SDL2_image.lib")
set(SDL2_IMAGE_DLLS 
	"${SDL2_IMAGE_PATH}/lib/x64/libpng16-16.dll"
	"${SDL2_IMAGE_PATH}/lib/x64/libjpeg-9.dll" 
	"${SDL2_IMAGE_PATH}/lib/x64/libtiff-5.dll" 
	"${SDL2_IMAGE_PATH}/lib/x64/libwebp-7.dll"
	"${SDL2_IMAGE_PATH}/lib/x64/SDL2_image.dll"
	"${SDL2_IMAGE_PATH}/lib/x64/zlib1.dll")

set(RESOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/assets/"
)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
					"${CMAKE_CURRENT_LIST_DIR}/sources/game/"
					"${CMAKE_CURRENT_LIST_DIR}/sources/ECS/"
					"${CMAKE_CURRENT_LIST_DIR}/sources/maze/"
					"${CMAKE_CURRENT_LIST_DIR}/sources/math/")

link_directories(${SDL2_LIBRARY} 
                 ${SDL2_IMAGE_LIBRARY}
				 ${CMAKE_CURRENT_LIST_DIR})	

set(SOURCE_FILES 
	"MazeGame.cpp"
	"sources/game/AssetManager.cpp"
	"sources/game/AssetManager.h"
	"sources/game/Game.cpp"
	"sources/game/Game.h"
	"sources/game/TextureManager.cpp"
	"sources/game/TextureManager.h"
	"sources/ECS/ECS.cpp"
	"sources/ECS/ECS.h"
	"sources/ECS/Components.h"
	"sources/ECS/SpriteComponent.h"
	"sources/ECS/TransformComponent.h"
	"sources/ECS/KeyboardController.h"
	"sources/ECS/ColliderComponent.h"
	"sources/ECS/TileComponent.h"
	"sources/ECS/ProjectileComponent.h"
	"sources/ECS/WallComponent.h"
	"sources/ECS/DoorComponent.h"
	"sources/math/Vector2D.h"
	"sources/math/Vector2D.cpp"
	"sources/math/Collision.cpp"
	"sources/math/Collision.h"
	"sources/maze/Door.cpp"
	"sources/maze/Door.h"
	"sources/maze/MapSite.h"
	"sources/maze/Maze.cpp"
	"sources/maze/Maze.h"
	"sources/maze/MazeBuilder.cpp"
	"sources/maze/MazeBuilder.h"
	"sources/maze/Room.cpp"
	"sources/maze/Room.h"
	"sources/maze/Wall.cpp"
	"sources/maze/Wall.h")

add_executable(MazeGame ${SOURCE_FILES})

add_custom_command(TARGET MazeGame 
	                      POST_BUILD
	                      COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_DLL} ${PROJECT_BINARY_DIR}
	                      COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_IMAGE_DLLS} ${PROJECT_BINARY_DIR}
	                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_FILES} "${PROJECT_BINARY_DIR}/assets/"
						  )


target_link_libraries(MazeGame PRIVATE ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

if(MSVC)
  target_compile_options(MazeGame PRIVATE /W4 /WX)
else()
  target_compile_options(MazeGame PRIVATE -Wall -Wextra -pedantic -Werror)
endif()