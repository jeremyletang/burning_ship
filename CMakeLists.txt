cmake_minimum_required (VERSION 2.6)

project (burning_ship)
 
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x -fopenmp")
add_executable(burning_ship src/main.cpp
							src/burning_ship.cpp
							src/params.cpp
							src/png_maker.cpp)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(burning_ship ${PNG_LIBRARY})