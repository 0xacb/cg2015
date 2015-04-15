#include <stdio.h>
#include <vector>
#include "object.hpp"

using namespace std;

class World {
	public:
		World();
		~World();
		vector<Object> objects;
		void load(const char* path);
};
