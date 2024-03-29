/*
	1. 시스템명 : BankingSystem
	2. 버전		: 1.0
	3. 담당자   : 임대섭
	4. 내용
		4.1 OOP(객체지향) 단계별 프로젝트의 기본 틀 구성

		1. 캡슐화, 정보은닉 적용
		2, 생성자, 소멸자 적용
		3, 객체 배열 적용
		4. 복사 생성자 적용
		5. const 키워드 적용
		6. 컨트롤 클래스, 엔터티 클래스 적용
*/

#include "MiniBankingCommonDecl.h"
#include "Account.h"





	//보통예금계좌 클래스
	class NormalAccount : public Account
	{
	private:
		double interRate; // 이자율
	public:
		NormalAccount(int ID, int money, char* name, double rate)
			:Account(ID,money,name), interRate(rate) {}

		void Deposit(int money)
		{
			Account::Deposit(money); // 원금 추가
			Account::Deposit((int)(money*interRate /100.0));//기본이자 추가
		}
	
	};

	//신용계좌 클래스
	class HighCreditAccount : public NormalAccount
	{
	private:
		double specialRate; // 특별 이자율
	public:
		HighCreditAccount(int ID, int money, char* name, double rate, double srate)
			:NormalAccount(ID,money,name,rate), specialRate(srate){}

		virtual void Deposit(int money)
		{
			NormalAccount::Deposit(money); // 원금기본이자 추가
			Account::Deposit((int)(money*specialRate/100.0)); //특별이자 추가
		}
	};


class AccountHandler
{
private:
	Account* accArr[100]; // Account 객체 저장을 위한 Account 객체 배열
	int accNum; // 등록된 계좌 수
	
public:
	//생성자
	AccountHandler() : accNum(0) {}
	void ShowMenu() const;	//메뉴 출력 함수
	void MakeAccount();		//계좌 개설 함수
	void DepositMoney();	// 입금하는 함수
	void WithdrawMoney();	//출금 하는 함수
	void ShowAllAccount() const;	// 전체계좌 출력 함수
	void MakeNormalAccount(); //보통예금계좌 개설 함수
	void MakeHighCreditAccount(); //신용신뢰계좌 개설 함수
	~AccountHandler();		//소멸자
};

//메뉴 출력 함수
void AccountHandler::ShowMenu() const
{
	cout << "----------Menum---------" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입금" << endl;
	cout << "3. 출금" << endl;
	cout << "4. 개좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

//계좌 개설 함수
void AccountHandler::MakeAccount()
{
	int select;

	cout << "[계좌 선택]" << endl;
	cout << "1. 보통예금계좌 ";
	cout << "2. 신용신뢰계좌 " << endl;
	cout << "선택  : "; cin >> select;

	switch (select)
	{
	case NORMAL:
		MakeNormalAccount();
		break;
	case CREDIT:
		MakeHighCreditAccount();
		break;
	}
}

//보통예금계좌 개설 함수
void AccountHandler::MakeNormalAccount()
{
	int id;
	char name[NAME_LEN];
	int balance;
	int interRate;

	cout << "[보통예금계좌개설]" << endl;
	cout << "계좌ID: ";	cin >> id;
	cout << "이름: ";	cin >> name;
	cout << "입금액: ";	cin >> balance;
	cout << "이자율: "; cin >> interRate;
	cout << endl;

	accArr[accNum++] = new NormalAccount(id, balance, name, interRate);
}

//신용신뢰계좌 개설 함수
void AccountHandler::MakeHighCreditAccount()
{
	int id;
	char name[NAME_LEN];
	int balance;
	int interRate;
	int creditRatingLV;

	cout << "[신용신뢰계좌개설]" << endl;
	cout << "계좌ID: ";	cin >> id;
	cout << "이름: ";	cin >> name;
	cout << "입금액: ";	cin >> balance;
	cout << "이자율: "; cin >> interRate;
	cout << "사용자 신용등급 A=1,B=2,C=3을 입력해주세요 : "; cin >> creditRatingLV;
	cout << endl;

	switch (creditRatingLV)
	{
	case 1:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_A);
		break;
	case 2:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_B);
		break;
	case 3:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_C);
		break;
	}
}

// 입금하는 함수
void AccountHandler::DepositMoney() 
{
	int money;
	int id;
	cout << "[입금]" << endl;
	cout << "계좌ID: ";
	cin >> id;
	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			cout << "입금액: ";
			cin >> money;
			accArr[i]->Deposit(money);
			
			cout << "입금 완료: " << endl;
			
			return;
		}
	}
	cout << "잘못된 계좌 번호 입력. " << endl;
}

//출금 하는 함수
void AccountHandler::WithdrawMoney()
{
	int money;
	int id;
	cout << "[출금]" << endl;
	cout << "계좌ID: ";
	cin >> id;
	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			if (accArr[i]->GetBalance() > 0)
			{
				cout << "출금액: ";
				cin >> money;
				accArr[i]->Withdraw(money);
				return;
			}
			else
			{
				cout << "잔액 모자람" << endl;
			}
		}
	}
	cout << "잘못된 계좌 번호 입력. " << endl;
}

// 전체계좌 출력 함수
void AccountHandler::ShowAllAccount() const
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->ShowAllAccount();
		cout << endl;
	}
}

//소멸자
AccountHandler::~AccountHandler()
{
	for (int i = 0; i < accNum; i++)
		delete accArr[i];
}

int main(void)
{
	AccountHandler AccHdr;
	int choice;

	while (1)
	{
		AccHdr.ShowMenu();
		cout << "선택: ";
		cin >> choice;
		cout << endl;
		
		switch (choice)
		{
		case MAKE:
			AccHdr.MakeAccount();
			break;
		case DEPOSIT:
			AccHdr.DepositMoney();
			break;
		case WITHDRAW:
			AccHdr.WithdrawMoney();
			break;
		case INQUIRE:
			AccHdr.ShowAllAccount();
			break;
		case EXIT:
			return 0;
		default:
			cout << "잘못된 메뉴 선택" << endl;
		}
	}

	system("pause");  // VC++ 에서만 필요

	return 0;
}





