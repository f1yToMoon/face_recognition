cmake_minimum_required(VERSION 2.8)
project(face)

set(CMAKE_CXX_STANDARD 14)

cmake_minimum_required(VERSION 2.8)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( face main.cpp i.cpp i.h)
target_link_libraries( face ${OpenCV_LIBS} )
