#include "world.hpp"

World::World(){}

World::~World(){}

void World::load(const char* path, GLdouble x, GLdouble y, GLdouble z) {
	Object *obj = new Object(path);
	obj->load();
	objects.push_back(obj);

	obj->x = x;
	obj->y = y;
	obj->z = z;
}

void World::render() {
	for (int i=0;i<(signed)objects.size();i++) {
		glPushMatrix();

		glTranslatef(objects[i]->x, objects[i]->y, objects[i]->z);
		objects[i]->render();

		glPopMatrix();
	}
}
