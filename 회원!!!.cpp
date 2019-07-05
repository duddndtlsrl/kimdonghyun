#include<iostream>
#include<string>
using namespace std;

typedef struct Member
{
	string ID;
	string PW;
	string PN;
	string Name;
	int Age;
	int Mileage;
};

void Register(Member* M, int* MCount)
{
	int Limit;
	string ConfirmPW;
	bool a=false, b = false;
	while (a == false)
	{
		system("cls");
		cout << "아이디 입력([3글자 이상] AND [한글X]) :" << endl;
		cin >> M->ID;
		Limit = M->ID.length();
		if (Limit < 3)
		{
			a = false;
			cout << "ID가 3글자 미만 입니다." << endl;
			system("pause");
			continue;
		}
		for (int i = 0; i < Limit; i++)
		{
			if (M->ID[i] >= '0' && M->ID[i] <= '9' || M->ID[i] >= 'a' && M->ID[i] <= 'z' || M->ID[i] >= 'A' && M->ID[i] <= 'Z')
				a = true;
			else
			{
				a = false;
				cout << "ID가 숫자나 영문이 아닙니다." << endl;
				system("pause");
				break;
			}
		}
	}
	a = false;
	while (a == false || b == false)
	{
		system("cls");
		cout << "비밀번호 입력 ([8글자 이상] AND [영문] AND [숫자 포함]) :" << endl;
		cin >> M->PW;
		Limit = M->PW.length();
		if (Limit < 8)
		{
			cout << "Password가 8글자 미만 입니다." << endl;
			system("pause");
			continue;
		}
		for (int i = 0; i < Limit; i++)
		{
			if (M->PW[i] >= '0' && M->PW[i] <= '9')
				a = true;
			else if (M->PW[i] >= 'a' && M->PW[i] <= 'z' || M->PW[i] >= 'A' && M->PW[i] <= 'Z')
				b = true;
		}
		if (a == false)
		{
			cout << "Password에 숫자가 포함되어있지 않습니다." << endl;
			system("pause");
			continue;
		}
		else if (b == false)
		{
			cout << "Password에 영문이 포함되어있지 않습니다." << endl;
			system("pause");
			continue;
		}
		cout << "비밀번호 확인 :" << endl;
		cin >> ConfirmPW;
		if (M->PW != ConfirmPW)
		{
			cout << "비밀번호가 일치하지 않습니다." << endl;
			system("pause");
		}
	}
	system("cls");
	cout << "닉네임 입력 :" << endl;
	cin >> M->Name;
	cout << "나이 입력 :" << endl;
	cin >> M->Age;
	cout << "휴대폰 번호 입력 :" << endl;
	cin >> M->PN;
	cout << "회원가입 성공!! 마일리지 1000원 등록" << endl;
	(*MCount)++;
	M->Mileage = 1000;
}

void Show(Member* M)
{
	cout << "=======회원 정보=======" << endl;
	cout << "ID : " << M->ID << "\t 닉네임 : " << M->Name << endl;
	cout << "나이: " << M->Age << "\t 휴대폰 번호 : " << M->PN << endl;
	cout << "마일리지 : " << M->Mileage << endl;
}

void UserInfo(Member* Mem)
{
	int Select, Num;
	string str;
	while (1)
	{
		system("cls");
		Show(Mem);
		cout << "=================" << endl;
		cout << "1.닉네임 변경" << endl;
		cout << "2.나이 변경" << endl;
		cout << "3.휴대폰 번호 변경" << endl;
		cout << "4.돌아가기" << endl;
		cout << "입력 :" << endl;
		cin >> Select;
		system("cls");
		switch (Select)
		{
		case 1:
			cout << "현재 닉네임: " << Mem->Name << endl;
			cout << "변경할 닉네임 입력: " << endl;
			cin >> str;
			Mem->Name = str;
			break;
		case 2:
			cout << "현재 나이: " << Mem->Name << endl;
			cout << "변경할 나이 입력: " << endl;
			cin >>Num;
			Mem->Age = Num;
			break;
		case 3:
			cout << "현재 번호: " << Mem->Name << endl;
			cout << "변경할 번호 입력: " << endl;
			cin >> str;
			Mem->PN = str;
			break;
		case 4:
			return;
		}
	}
}


void User_Menu(Member* Mem)
{
	int Select1;
	while (1)
	{
		system("cls");
		cout << "=====Menu=====" << endl;
		cout << "  1. 회원 정보" << endl;
		cout << "  2. 회원 정보 변경" << endl;
		cout << "  3. 로그아웃" << endl;
		cin >> Select1;
		system("cls");
		switch (Select1)
		{
		case 1:
			Show(Mem);
			system("pause");
			break;
		case 2:
			UserInfo(Mem);
			system("pause");
			break;
		case 3:
			return;
		}
	}
}

void Login(Member M[], Member* Mem)
{
	bool a = false, b = false;
	string ID;
	string PW;
	int Num;
	while (a == false || b == false)
	{
		cout << "아이디 입력 :" << endl;
		cin >> ID;
		cout << "비밀번호 입력 :" << endl;
		cin >> PW;
		for (int i = 0; i < 10; i++)
		{
			if (M[i].ID == ID)
			{
				a = true;
				Num = i;
				break;
			}
		}
		if (M[Num].PW == PW)
			b = true;
	}
	Mem = &M[Num];
	User_Menu(Mem);
}

void Menu(int MCount)
{
	cout << "=====Login=====(회원수[" << MCount << "명])" << endl;
	cout << "\t1. 회원 가입" << endl;
	cout << "\t2. 로그인" << endl;
	cout << "\t3. 종료" << endl;
	cout << "입력 :" << endl;
}

void main()
{
	Member M[10];
	int MCount=0;
	int Select;
	int MNum;
	Member* Mem = &M[MCount];
	while (1)
	{
		system("cls");
		Menu(MCount);
		cin >> Select;
		system("cls");
		switch (Select)
		{
		case 1:
			if (MCount >= 10)
			{
				cout << "잘못된 접근입니다." << endl;
				break;
			}
			else
			{
				Register(Mem, &MCount);
				break;
			}
		case 2:
			Login(M, Mem);
			break;
		case 3:
			return;
		}
	}
}



