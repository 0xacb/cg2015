#include "world.hpp"

World::World(){}

World::~World(){}

void World::load(const char* path) {
	Object obj(path);
	obj.load();
	objects.push_back(obj);
}

void World::render() {
	for (int i=0;i<(signed)objects.size();i++) {
		objects[i].render();
	}
}
