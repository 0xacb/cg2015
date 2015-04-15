#include "world.hpp"

World::World(){}

World::~World(){}

void World::load(const char* path) {
	Object obj(path);
	obj.load();
	objects.push_back(obj);
}
