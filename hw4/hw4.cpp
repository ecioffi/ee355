#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class Circle {
	public:
		float x, y, r;
		Circle(float x, float y, float r) : x(x), y(y), r(r) { }
};

class hw4_2 {
	public:
		static float centerDistance(Circle a, Circle b)
		{
			return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
		}

		static float commonArea(Circle a, Circle b)
		{
			float d = centerDistance(a, b);
			return pow(a.r, 2) * acos((pow(d, 2) + pow(a.r, 2) - pow(b.r, 2)) / (2*d*a.r)) +
				pow(b.r, 2) * acos((pow(d, 2) + pow(b.r, 2) - pow(a.r, 2)) / (2*d*b.r)) -
				0.5 * sqrt((-d + a.r + b.r) * (d + a.r - b.r) * (d - a.r + b.r) * (d + a.r + b.r));
		}
};

int main()
{
	srand(time(0));

	cout << "Overlapping area between 15 random circles (x, y, r), (x', y', r'):" << endl;
	cout << "(x, y) refers to the circle center, and r the radius." << endl;
	cout << "If the result is nan, then the circles do not intersect." << endl << endl;

	for (int i = 0; i < 15; i++)
	{
		Circle a(rand() % 10, rand() % 10, rand() % 10);
		Circle b(rand() % 10, rand() % 10, rand() % 10);
		cout << "Area between (" << a.x << ", " << a.y << ", " << a.r << ") and ";
		cout << "(" << b.x << ", " << b.y << ", " << b.r << ") is " << hw4_2::commonArea(a, b) << endl;
	}
	return 0;
}