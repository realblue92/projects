#include <stdio.h>
#include <string.h>
# define max_lth_name 15 //최대 이름 길이
# define max_lth_id 15 //최대 계좌번호 길이
# define max_lth_pw 5 //최대 비밀번호 길이
# define max_member 100 //최대 계좌등록가능 인원 수
# define admin_pw "0000" //관리자 비밀번호
struct Account //구조체 account 정의
{
	char name[max_lth_name];		// 이름(예금주명)
	char id[max_lth_id];			// 계좌번호
	char pw[max_lth_pw];			// 비밀번호 4자리
	int balance[max_member];		// 잔액
	int transfer_save[max_member];	// 계좌이체시 출금->송금 저장소
};

Account member[max_member] = { 0 };
int add_account(int count);			//1.계좌등록
int balance_inquiry(int view);		//5. 잔액 조회
int admin(int total);				//6. 관리자 메뉴

int input(int member_count);		// 입금 기능
int check_id(int memberaccount);	// 계좌번호 체크
int check_pw(int);					// 계좌 비밀번호 체크

int number = 0;						// 계좌 등록자 초기화

int add_account(int count) {			//1.계좌등록
	for (count; count < max_member; count++) {
		printf("귀하의 성함을 입력해주세요.\n");
		scanf("%s", member[count].name);
		printf("등록하실 계좌의 비밀번호를 입력해주세요.(숫자 4자리)\n");
		scanf("%s", member[count].pw);
		printf("bangpe은행은 계좌번호를 휴대전화번호로 제공하고 있습니다.\n휴대전화번호를 하이픈(-)없이 입력해주세요.\n");
		scanf("%s", member[count].id);
		printf("%s 님의 계좌가 개설되었습니다. \n귀하의 계좌번호는 %s입니다.\n", member[count].name, member[count].id);
		return count;
	}
}
int check_id(int memberaccount) {	// 계좌번호 체크 (2.입금 3.출금 4.계좌이체 5.잔액 조회 시 사용)
	int checked;
	char input[max_lth_id];
	while (1) {
		printf("계좌번호를 입력해주세요.\n");
		scanf("%s", input);
		for (checked = 0; checked < memberaccount; checked++) {
			if ((char)strcmp(input, member[checked].id) == 0) {
				return checked;
			}
		}
		printf("등록되지 않은 계좌입니다.\n");
		continue;
	}
}
int check_pw(int id) {				// 계좌 비밀번호 체크 (2.입금 3.출금 4.계좌이체 5.잔액 조회 시 사용)
	char input[max_lth_pw];
	while (1) {
		printf("비밀번호를 입력해주세요.\n");
		scanf("%s", input);
		if ((char)strcmp(input, member[id].pw) == 0) {
			return id;
		}
		printf("비밀번호가 일치하지 않습니다.\n");
		continue;
	}
}
int balance_inquiry(int view) {		//5. 잔액 확인
	printf("%s 님 계좌의 잔액은 %d 원 입니다.\n", member[view].name, *member[view].balance);
	return 0;
}
int admin(int total) {				//6. 관리자 메뉴	
	char input[max_lth_pw];
	while (1) {
		printf("비밀번호를 입력해주세요.\n");
		scanf("%s", input);
		if ((char)strcmp(input, admin_pw) == 0) {
			printf("번호\t예금주명\t계좌번호\t현재잔액\n");
			for (int zero = 0; zero < total; zero++) {
				printf("%d\t%s\t\t%s\t%d\n", zero + 1, member[zero].name, member[zero].id, *member[zero].balance);
				return 0;
			}
		}
		else {
			printf("비밀번호가 일치하지 않습니다.\n");
			continue;
		}
	}
}
int input(int member_count) {	// 입금
	int money[max_member];
	while (1) {
		printf("계좌에 입금하실 금액을 입력해주세요.\n");
		scanf("%d", &money[member_count]);
		if (*member[member_count].balance == 0) {
			if (money[member_count] <= 0) {
				printf("잘못된 입력입니다.\n");
				continue;
			}
			else {
				*member[member_count].balance = money[member_count];
				printf("입금되었습니다.\n");
				member_count++;
				number = member_count;
				return member_count;
			}
		}
		else {
			if (money[member_count] <= 0) {
				printf("잘못된 입력입니다.\n");
				continue;
			}
			else {
				*member[member_count].balance += money[member_count];
				printf("입금되었습니다.\n");
				return 0;
			}
		}
	}
}
int transfer_input(int minus, int plus) {// 계좌이체 후 송금
	*member[plus].balance += *member[minus].transfer_save;
	printf("송금되었습니다.\n");
	return 0;
}
int takeout(int member_count) {			// 출금
	int money[max_member];
	for (int count = 0; count < max_member; count++) {
		money[count] = { 0 };
	}
	while (1) {
		printf("계좌에서 출금하실 금액을 입력해주세요.\n");
		scanf("%d", &money[member_count]);
		if (money[member_count] > *member[member_count].balance) {
			printf("잔액이 부족합니다.\n");
			continue;
		}
		*member[member_count].balance = *member[member_count].balance - money[member_count];
		*member[member_count].transfer_save = money[member_count];
		printf("출금되었습니다.\n");
		return member_count;
	}
}
int main() {
	int mainmenu, money, plusmoney, minusmoney, deposit, withdrawal, searched;
	while (1) {
		printf("bangpe은행에 오신걸 환영합니다.\n1.계좌등록\n2.입금\n3.출금\n4.계좌이체\n5.잔액조회\n6.관리자메뉴\n메뉴를 입력해주세요.\n");
		scanf("%d", &mainmenu);
		switch (mainmenu) {
		case 1: printf("계좌등록을 선택하셨습니다.\n");
			money = add_account((int)number);
			input((int)money);
			break;
		case 2: printf("입금을 선택하셨습니다.\n");
			plusmoney = check_id((int)number);
			deposit = check_pw((int)plusmoney);
			input((int)deposit);
			break;
		case 3: printf("출금을 선택하셨습니다.\n");
			minusmoney = check_id((int)number);
			withdrawal = check_pw((int)minusmoney);
			takeout((int)withdrawal);
			break;
		case 4: printf("계좌이체를 선택하셨습니다.\n");
			printf("출금하실 ");
			minusmoney = check_id((int)number);
			withdrawal = check_pw((int)minusmoney);
			takeout((int)withdrawal);
			printf("송금하실 ");
			plusmoney = check_id((int)number);
			transfer_input((int)minusmoney, plusmoney);
			break;
		case 5: printf("잔액조회를 선택하셨습니다.\n");
			plusmoney = check_id((int)number);
			searched = check_pw((int)plusmoney);
			balance_inquiry((int)searched);
			break;
		case 6: printf("관리자 메뉴입니다.\n");
			admin((int)number);
			break;
		default:printf("잘못된 선택입니다. 메뉴를 입력해주세요.\n");
			break;
		}
		continue;
	}
	return 0;
}