cmake_minimum_required(VERSION 2.8)
project(face_hist)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(face_hist main.cpp)
target_link_libraries(face_hist ${OpenCV_LIBS} )