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

void World::load(Object *obj) {
	obj->load();
	objects.push_back(obj);
}

void World::update() {
	for (int i = 0; i < (int) objects.size(); i++) {
		objects[i]->update();
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
