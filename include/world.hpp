#ifndef WORLD_HPP
#define WORLD_HPP

#include <stdio.h>
#include <vector>
#include <algorithm>

#include "main.hpp"
#include "object.hpp"
#include "sphere.hpp"
#include "sea.hpp"

#include <GLFW/glfw3.h>

using namespace std;

class World {
	public:
		World();
		~World();

		GLFWwindow *window;

		GLfloat cubeSide = 60.0f;
		GLfloat cubeHeight = 40.0f;

		Camera camera;

		Skybox skybox;
		Sea sea;

		bool canAddSphere = true;

		vector<Object*> objects;
		vector<Sphere*> spheres;
		double size = 1000;
		void load(const char* path, GLdouble x, GLdouble y, GLdouble z, GLfloat opacity);
		void load(const char* path, GLdouble x, GLdouble y, GLdouble z);
		void load(Object *obj, string type);
		void update();
		void render();
};

#endif
