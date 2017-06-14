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
	NameCard(NameCard &copy)
		:position(copy.position)
	{
		name = new char[strlen(copy.name) + 1];
		company = new char[strlen(copy.company) + 1];
		number = new char[strlen(copy.number) + 1];
		strcpy(name, copy.name);
		strcpy(company, copy.company);
		strcpy(number, copy.number);
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
	NameCard copy1 = manClerk;
	NameCard manSENIOR("HONG", "OrangeEng", "010-3333-4444", COMP_POS::SENIOR);
	NameCard copy2 = manSENIOR;
	manClerk.ShowNameCardInfo();
	manSENIOR.ShowNameCardInfo();
	copy1.ShowNameCardInfo();
	copy2.ShowNameCardInfo();
	return 0;
}