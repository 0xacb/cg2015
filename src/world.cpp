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

	printf("%f\n", spheres[0]->y);
	printf("%f %f\n", fabs(spheres[0]->y), cubeHeight);

	for (int i = 0; i < (int) spheres.size(); i++) {
		for (int u = i + 1; u < (int) spheres.size(); u++) {
			if (spheres[i]->isColliding(spheres[u])) {
				//GLfloat redColor[4] = {1.0, 0.0, 0.0, 1.0};

				GLfloat newColor[4] = {(spheres[i]->color[0] + spheres[i]->color[0]) / 2,
													  (spheres[i]->color[1] + spheres[i]->color[1]) / 2,
					    							 (spheres[i]->color[2] + spheres[i]->color[2]) / 2,
														1.0f};

														memcpy(spheres[i]->color, newColor, sizeof(newColor));
														memcpy(spheres[u]->color, newColor, sizeof(newColor));

			}
		}

		if (fabs(spheres[i]->x) >= cubeSide || fabs(spheres[i]->y) + spheres[i]->radius >= cubeHeight || fabs(spheres[i]->z) >= cubeSide) {
			if (i == 0) printf("SPHERE COLLIDING\n");

			spheres[i]->vx = -spheres[i]->vx;
			spheres[i]->vy = -spheres[i]->vy;
			spheres[i]->vz = -spheres[i]->vz;
		}
	}

	GLfloat yellowColor[4] = {0.0, 1.0, 1.0, 1.0};
	memcpy(spheres[0]->color, yellowColor, sizeof(yellowColor));
}

void World::render() {
	for (int i = 0; i<(signed)objects.size(); i++) {
		glPushMatrix();
			glTranslatef(objects[i]->x, objects[i]->y, objects[i]->z);
			objects[i]->render();
		glPopMatrix();
	}
}
