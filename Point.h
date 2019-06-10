#include <math.h>
struct Point {
	int x, y;
	Point(int int1, int int2) : x(int1), y(int2) {}
	int getDistance(Point p2) {
		Point p1 = *this;
		return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	}
};
