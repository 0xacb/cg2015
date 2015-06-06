#include "Sphere.hpp"

Sphere::Sphere(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _radius) {
	x = _x;
	y = _y;
	z = _z;
	radius = _radius;

	vx = randomFloat(-0.1, 0.1);
	//vy = randomFloat(-0.1, 0.1);
	vy = 0;
	vz = randomFloat(-0.1, 0.1);
}

void Sphere::update() {
	x += vx;
	y += vy;
	z += vz;


}

void Sphere::render() {
	GLfloat colorWhite[4] = {1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	gluSphere(gluNewQuadric(), radius, 24, 24);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorWhite);
};

bool Sphere::isColliding(Sphere *otherSphere) {
	GLfloat dx = abs(x - otherSphere->x);
	GLfloat dy = abs(y - otherSphere->y);
	GLfloat dz = abs(z - otherSphere->z);

	float distance = dx * dx + dy * dy + dz * dz;
	float minDistance = radius + otherSphere->radius;

	return minDistance >= distance * distance;
}
