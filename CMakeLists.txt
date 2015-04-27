set (PROJECT_NAME "cg2015")

set (CMAKE_CXX_FLAGS "-std=c++0x -Wall")

project (${PROJECT_NAME})
cmake_minimum_required (VERSION 2.8)

set (INCLUDE_DIR ./include/)
include_directories (${INCLUDE_DIR})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories (${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

file (GLOB_RECURSE PROJECT_INCLUDES "include/*.hpp")
file (GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")

include_directories (PROJECT_INCLUDES)
add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries (${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
