cmake_minimum_required(VERSION 2.8)
project(face_resize)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(face_resize main_resize.cpp)
target_link_libraries(face_resize ${OpenCV_LIBS} )
