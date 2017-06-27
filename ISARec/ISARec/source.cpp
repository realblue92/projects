#include <iostream>
using namespace std;

class Rectangle
{
private:
	int x, y;
public:
	Rectangle(int Hori, int Vert) : x(Hori), y(Vert)	// Rectangle 클래스 생성자(초기화)
	{

	}
	void ShowAreaInfo()	// 면적(x,y의 곱) 출력
	{
		cout << "면적:" << x*y << endl;
	}
};

class Square : public Rectangle // 상속 선언 : Square (자식) , Rectangle (부모)
{

public:
	Square(int segment) : Rectangle(segment, segment)	// Square 클래스 생성자(초기화), 이 때 Rectangle 클래스 생성자(초기화) 이용
	{
	}
};

int main()
{
	Rectangle rec(4, 3);	// Rectangle 클래스를 갖는 rec 객체 생성 및 인자 값 입력
	rec.ShowAreaInfo();		// rec 면적 출력

	Square sqr(7);			// Square 클래스를 갖는 sqr 객체 생성 및 인자 값 입력
	sqr.ShowAreaInfo();		// sqr 면적 출력
	return 0;
}