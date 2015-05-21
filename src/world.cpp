#include "world.hpp"

World::World(){}

World::~World(){}

void World::load(const char* path) {
	Object *obj = new Object(path);
	obj->load();
	objects.push_back(obj);

	/*Sphere *sphere = new Sphere("obj/monkey.obj");
	sphere->load();
	objects.push_back(sphere);*/
}

void World::render() {
	for (int i=0;i<(signed)objects.size();i++) {
		objects[i]->render();
	}
}
