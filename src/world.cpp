#include "world.hpp"

World::World(){}

World::~World(){}

void World::load(const char* path, GLdouble x, GLdouble y, GLdouble z, GLfloat opacity) {
	Object *obj = new Object();
	obj->path = path;
	obj->load();
	objects.push_back(obj);

	obj->x = x;
	obj->y = y;
	obj->z = z;
	obj->opacity = opacity;
}

void World::load(Object *obj, string type) {
	obj->load();
	objects.push_back(obj);

	if (type == "sphere") {
		spheres.push_back((Sphere*) obj);
	}
}

void World::update() {
	for (int i = 0; i < (int) objects.size(); i++) {
		objects[i]->update();
	}

	for (int i = 0; i < (int) spheres.size(); i++) {
		for (int u = i + 1; u < (int) spheres.size(); u++) {
			if (spheres[i]->isColliding(spheres[u])) {
				GLfloat redColor[4] = {1.0, 0.0, 0.0, 1.0};

				memcpy(spheres[i]->color, redColor, sizeof(redColor));
				memcpy(spheres[u]->color, redColor, sizeof(redColor));
			}
		}
	}
}

void World::render() {
	for (int i = 0; i<(signed)objects.size(); i++) {
		glPushMatrix();
			glTranslatef(objects[i]->x, objects[i]->y, objects[i]->z);
			objects[i]->render();
		glPopMatrix();
	}
}
