#include <stdio.h>
#include <vector>
#include <GL/glut.h>

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
		vector<Sphere*> spheres;
		double size;
		void load(const char* path, GLdouble x, GLdouble y, GLdouble z, GLfloat opacity);
		void load(const char* path, GLdouble x, GLdouble y, GLdouble z);
		void load(Object *obj, string type);
		void update();
		void render();
};
