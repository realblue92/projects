#include <iostream>
using namespace std;

class Rectangle
{
private:
	int x, y;
public:
	Rectangle(int Hori, int Vert) : x(Hori), y(Vert)
	{

	}
	void ShowAreaInfo()
	{
		cout << "¸éÀû:" << x*y << endl;
	}
};

class Square : public Rectangle
{

public:
	Square(int segment) : Rectangle(segment, segment)
	{
	}
};

int main()
{
	Rectangle rec(4, 3);
	rec.ShowAreaInfo();

	Square sqr(7);
	sqr.ShowAreaInfo();
	return 0;
}