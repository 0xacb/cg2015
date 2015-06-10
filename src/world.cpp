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

	vector<int> toRemove;
	vector<bool> canCollide(spheres.size(), true);

	for (int i = 0; i < (int) spheres.size(); i++) {
		for (int u = i + 1; u < (int) spheres.size(); u++) {
			if (spheres[i]->isColliding(spheres[u]) && canCollide[i]) {
				printf("Collision happening.\n");

				GLfloat newColor[4] = {(spheres[i]->color[0] + spheres[i]->color[0]) / 2,
					(spheres[i]->color[1] + spheres[i]->color[1]) / 2,
					(spheres[i]->color[2] + spheres[i]->color[2]) / 2,
					1.0f};

				memcpy(spheres[i]->color, newColor, sizeof(newColor));
				memcpy(spheres[u]->color, newColor, sizeof(newColor));

				spheres[u]->radius *= 1.5;

				toRemove.push_back(i);
				canCollide[u] = false;
				break;
			}
		}

		if (fabs(spheres[i]->x) >= cubeSide ||
		 	  fabs(spheres[i]->y) + spheres[i]->radius >= cubeHeight ||
				fabs(spheres[i]->z) >= cubeSide) {
			spheres[i]->vx = -spheres[i]->vx;
			spheres[i]->vy = -spheres[i]->vy;
			spheres[i]->vz = -spheres[i]->vz;
		}
	}

 vector<int>::iterator it = unique(toRemove.begin(), toRemove.end());
	toRemove.resize(distance(toRemove.begin(), it));
	printf("%d, %d\n", (int) toRemove.size(), (int) spheres.size());

	for (int i = toRemove.size() - 1; i >= 0; i--) {
		spheres.erase(spheres.begin() + toRemove[i]);
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
