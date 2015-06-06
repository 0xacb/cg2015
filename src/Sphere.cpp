#include "Sphere.hpp"

Sphere::Sphere(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _radius) {
	printf("lel %f\n", _x);

	x = _x;
	y = _y;
	z = _z;
	radius = _radius;
}

void Sphere::update() {
}

void Sphere::render() {
	printf("rendering %f\n", x);

	GLfloat colorBlue[4] = {0.0, 0.2, 1.0, 1.0};
	GLfloat colorWhite[4] = {1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);
	gluSphere(gluNewQuadric(), radius, 24, 24);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorWhite);
};

bool Sphere::isColliding(Sphere *otherSphere) {
	GLfloat dx = abs(x - otherSphere->x);
	GLfloat dy = abs(y - otherSphere->y);
	GLfloat dz = abs(z - otherSphere->z);

	float distance = dx * dx + dy * dy + dz * dz;
	float minDistance = radius + otherSphere->radius;

	return minDistance <= distance * distance;
}
