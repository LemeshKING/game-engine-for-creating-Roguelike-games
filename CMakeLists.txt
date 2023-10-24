cmake_minimum_required (VERSION 3.27 FATAL_ERROR)

set(PROJECT_NAME VKR)
set(SOURCES_FILES src/main.cpp)

project(${PROJECT_NAME})


if(CMAKE_BUILD_TYPE STREQUAL "Release")
	add_executable(${PROJECT_NAME} WIN32 ${SOURCES_FILES})
else ()
	add_executable(${PROJECT_NAME} ${SOURCES_FILES})
endif ()
set(SFML_DIR "C:/hz/учеба/Диплом/game/SFML-2.6.0/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)
endif()