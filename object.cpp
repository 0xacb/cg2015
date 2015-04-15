#include <GL/gl.h>
#include "object.hpp"

#define MAXLEN 100

using namespace std;

Object::Object(const char* path) {
	this->path = path;
}

Object::~Object(){}

vector <point> tmpVerts;
vector <point> tmpNormals;
vector <face> tmpFaces;

bool Object::load() {
	point p;

	FILE *f = fopen(this->path, "r");
	if (!f) return false;

	char line[MAXLEN];
	double x = 0, y = 0, z = 0;
	int conn[6];
	while(fgets(line, MAXLEN, f)) {
		switch (line[0]) {
			case 'v':
				sscanf(line+2, "%lf %lf %lf", &x, &y, &z);
				p = {x, y, z};
				if (line[1] == ' ') {
					tmpVerts.push_back(p);
				}
				else if (line[1] == 'n') {
					tmpNormals.push_back(p);
				}
				break;
			case 'f':
				sscanf(line+2, "%d//%d %d//%d %d//%d", &conn[0], &conn[1], &conn[2], &conn[3], &conn[4], &conn[5]);
				face cf;
				cf.points.push_back(&tmpVerts[conn[0]-1]);
				cf.points.push_back(&tmpVerts[conn[2]-1]);
				cf.points.push_back(&tmpVerts[conn[4]-1]);
				cf.normals.push_back(&tmpNormals[conn[1]-1]);
				cf.normals.push_back(&tmpNormals[conn[3]-1]);
				cf.normals.push_back(&tmpNormals[conn[5]-1]);
				tmpFaces.push_back(cf);
				break;
		}
	}
	this->verts = tmpVerts;
	this->normals = tmpNormals;
	this->faces = tmpFaces;
	return true;
}

void Object::render() {
	int i;
	glBegin(GL_TRIANGLES);
		for (i=0;i<(signed)this->faces.size();i++) {
			glNormal3f(this->faces[i].normals[0]->x, this->faces[i].normals[0]->y, this->faces[i].normals[0]->z);
			glVertex3f(this->faces[i].points[0]->x, this->faces[i].points[0]->y, this->faces[i].points[0]->z);
			glNormal3f(this->faces[i].normals[1]->x, this->faces[i].normals[1]->y, this->faces[i].normals[1]->z);
			glVertex3f(this->faces[i].points[1]->x, this->faces[i].points[1]->y, this->faces[i].points[1]->z);
			glNormal3f(this->faces[i].normals[2]->x, this->faces[i].normals[2]->y, this->faces[i].normals[2]->z);
			glVertex3f(this->faces[i].points[2]->x, this->faces[i].points[2]->y, this->faces[i].points[2]->z);
		}
	glEnd();
}
