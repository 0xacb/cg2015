#include <stdio.h>
#include <vector>
#include <gl/glut.h>

#include "camera.hpp"
#include "skybox.hpp"
#include "object.hpp"
#include "Sphere.hpp"

using namespace std;

class World {
	public:
		World();
		~World();

		Camera camera;

		Skybox skybox;
		vector<Object*> objects;
		double size;
		void load(const char* path, GLdouble x, GLdouble y, GLdouble z);
		void load(Object *obj, GLdouble x, GLdouble y, GLdouble z);
		void render();
};
