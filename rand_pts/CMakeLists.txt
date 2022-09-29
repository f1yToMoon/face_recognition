cmake_minimum_required(VERSION 2.8)
project(face)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( face rand_pts.cpp )
target_link_libraries( face ${OpenCV_LIBS} )
