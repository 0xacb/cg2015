#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <stdio.h>
#include <vector>
#include "structs.hpp"

using namespace std;

class Object {
	public:
		Object(const char* path);
		~Object();
		const char* path;
		vector <point> verts;
		vector <point> normals;
		vector <face> faces;
		bool load();
		virtual void render();
};

#endif
