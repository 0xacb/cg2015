set (PROJECT_NAME "cg2015")

if (APPLE)
  set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -g -framework OpenGl -lglfw3 -framework sfml-audio")
ELSE (NOT APPLE)
  set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -g -lGLEW -lGL -lGLU -lglfw -lsfml-audio")
ENDIF (APPLE)

project (${PROJECT_NAME})
cmake_minimum_required (VERSION 2.8)

set (INCLUDE_DIR ./include/)
include_directories (${INCLUDE_DIR})

#find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)

file (GLOB_RECURSE PROJECT_INCLUDES "include/*.hpp")
file (GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")
#${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS}

#ADD_DEFINITIONS(
#    -lGL
#    -lGLU
#    -lGLEW
#    -lglfw
#)

include_directories (PROJECT_INCLUDES)
add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries (${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
