#include <iostream>
using namespace std;

class Rectangle
{
private:
	int x, y;
public:
	Rectangle(int Hori, int Vert) : x(Hori), y(Vert)	// Rectangle Ŭ���� ������(�ʱ�ȭ)
	{

	}
	void ShowAreaInfo()	// ����(x,y�� ��) ���
	{
		cout << "����:" << x*y << endl;
	}
};

class Square : public Rectangle // ��� ���� : Square (�ڽ�) , Rectangle (�θ�)
{

public:
	Square(int segment) : Rectangle(segment, segment)	// Square Ŭ���� ������(�ʱ�ȭ), �� �� Rectangle Ŭ���� ������(�ʱ�ȭ) �̿�
	{
	}
};

int main()
{
	Rectangle rec(4, 3);	// Rectangle Ŭ������ ���� rec ��ü ���� �� ���� �� �Է�
	rec.ShowAreaInfo();		// rec ���� ���

	Square sqr(7);			// Square Ŭ������ ���� sqr ��ü ���� �� ���� �� �Է�
	sqr.ShowAreaInfo();		// sqr ���� ���
	return 0;
}