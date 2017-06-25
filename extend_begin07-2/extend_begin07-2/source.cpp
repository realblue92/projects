#include <iostream>
using namespace std;

class  MyFriendInfo
{
public:
	MyFriendInfo()
	{}
	 MyFriendInfo(int friendage ,char * friendname)
	 {
		 age = friendage;
		 name = new char[strlen(friendname) + 1];
		 strcpy(name, friendname);
	 }

	void ShowMyFriendInfo()
	{
		cout << "�̸�: " << name << endl;
		cout << "����: " << age << endl;
	}
private:
	char * name;
	int age;
};

class  MyFriendDetailInfo : public MyFriendInfo
{
public:
	MyFriendDetailInfo() : MyFriendInfo()
	{}
	MyFriendDetailInfo(int friendage, char * friendname, char * friendaddr, char * friendphone) : MyFriendInfo(friendage, friendname)
	{
		addr = new char[strlen(friendaddr) + 1];
		strcpy(addr, friendaddr);
		phone = new char[strlen(friendphone) + 1];
		strcpy(phone, friendphone);
	}
	void ShowMyFriendDetailInfo()
	{
		ShowMyFriendInfo();
		cout << "�ּ�: " << addr << endl;
		cout << "��ȭ: " << phone << endl;
	}
private:
	char * addr;
	char * phone;
};

int main()
{
	MyFriendDetailInfo Jackass(15, "Jackass", "nowhere", "010-0000-0000");
	Jackass.ShowMyFriendDetailInfo();
	return 0;
}
