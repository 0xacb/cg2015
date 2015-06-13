#include <stdio.h>
#include <vector>
#include <algorithm>

#include "main.hpp"
#include "object.hpp"
#include "sphere.hpp"
#include "sea.hpp"

using namespace std;

class World {
	public:
		World();
		~World();

		GLfloat cubeSide = 50.0f;
		GLfloat cubeHeight = 40.0f;

		Camera camera;

		Skybox skybox;
		Sea sea;

		vector<Object*> objects;
		vector<Sphere*> spheres;
		double size = 1000;
		void load(const char* path, GLdouble x, GLdouble y, GLdouble z, GLfloat opacity);
		void load(const char* path, GLdouble x, GLdouble y, GLdouble z);
		void load(Object *obj, string type);
		void update();
		void render();
};
