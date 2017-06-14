#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

namespace COMP_POS
{
	enum
	{
		CLERK, SENIOR, ASSIST, MANAGER
	};

	void ShowPosInfo(const int pos)
	{
		switch (pos)
		{
		case CLERK:
			cout << "사원" << endl;
			break;
		case SENIOR:
			cout << "주임" << endl;
			break;
		case ASSIST:
			cout << "대리" << endl;
			break;
		case MANAGER:
			cout << "과장" << endl;
			break;
		}
	}
}


class NameCard
{
private:
	char *name;
	char *company;
	char *number;
	int position;
public:
	NameCard(char *myname, char *mycompany, char *mynumber, int myposition)
	{
		int namelen = strlen(myname) + 1;
		name = new char[namelen];         // 이름 정보 동적할당
		strcpy(name, myname);
		int complen = strlen(mycompany) + 1;
		company = new char[complen];      // 회사 정보 동적할당
		strcpy(company, mycompany);
		int numlen = strlen(mynumber) + 1;
		number = new char[numlen];         // 전화번호 정보 동적할당
		strcpy(number, mynumber);
		position = myposition;
	}
	void ShowNameCardInfo() const
	{

		cout << "이름: " << name << endl;
		cout << "회사: " << company << endl;
		cout << "전화번호: " << number << endl;
		cout << "직급: "; COMP_POS::ShowPosInfo(position);
		cout << endl;
	}
	~NameCard()
	{
		delete[]name;
		delete[]company;
		delete[]number;
	}
};
int main()
{
	NameCard manClerk("Lee", "ABCEng", "010-1111-2222", COMP_POS::CLERK);
	NameCard manSENIOR("HONG", "OrangeEng", "010-3333-4444", COMP_POS::SENIOR);
	NameCard manAssist("Kim", "SoGoodComp", "010-5555-6666", COMP_POS::ASSIST);
	manClerk.ShowNameCardInfo();
	manSENIOR.ShowNameCardInfo();
	manAssist.ShowNameCardInfo();

	return 0;
}