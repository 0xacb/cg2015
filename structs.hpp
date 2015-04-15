#include <vector>

using namespace std;

struct point {
	double x;
	double y;
	double z;
};

struct face {
	vector <point*> points;
	vector <point*> normals;
};
