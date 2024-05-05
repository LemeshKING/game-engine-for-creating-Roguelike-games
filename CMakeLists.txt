cmake_minimum_required (VERSION 3.27 FATAL_ERROR)

set(PROJECT_NAME VKR)
set(SOURCES_FILES src/main.cpp 
    src/proceduralgeneration/ProceduralGeneration.h
	src/proceduralgeneration/ProceduralGeneration.cpp
	src/Shaders.frag
	src/player/player.h
	src/player/player.cpp
	src/AnimationManager/AnimationManager.h
	src/AnimationManager/AnimationManager.cpp
	src/Camera/Camera.h
	src/Camera/Camera.cpp
	src/character/character.h
	src/character/character.cpp
	src/enemy/enemy.h
	src/enemy/enemy.cpp
	src/game/game.h
	src/game/game.cpp
	src/Map/map.h
	src/Map/map.cpp
	src/Health/health.h
	src/Health/health.cpp
	src/Weapon/weapon.h
	src/Weapon/weapon.cpp
	src/bow/bow.h
	src/bow/bow.cpp
	src/sword/sword.h
	src/sword/sword.cpp
	src/Tile/Tile.h
	src/Tile/Tile.cpp
	src/GameObject/GameObject.h
	src/GameObject/GameObject.cpp
	src/thorns/thorns.h
	src/thorns/thorns.cpp
	src/teleport/teleport.h
	src/teleport/teleport.cpp
	src/Wizard/wizard.h
	src/Wizard/wizard.cpp
	src/ProjectTile/ProjectTile.h
	src/ProjectTile/ProjectTile.cpp
	src/HealthBar/HealthBar.h
	src/HealthBar/HealthBar.cpp
	src/Animation/Animation.h
	src/Animation/Animation.cpp)
	
project(${PROJECT_NAME})


if(CMAKE_BUILD_TYPE STREQUAL "Release")
	add_executable(${PROJECT_NAME} WIN32 ${SOURCES_FILES})
else ()
	add_executable(${PROJECT_NAME} ${SOURCES_FILES})
endif ()
set(SFML_DIR "external/SFML-2.6.0/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)
endif()