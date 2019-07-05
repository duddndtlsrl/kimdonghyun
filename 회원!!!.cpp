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
		cout << "���̵� �Է�([3���� �̻�] AND [�ѱ�X]) :" << endl;
		cin >> M->ID;
		Limit = M->ID.length();
		if (Limit < 3)
		{
			a = false;
			cout << "ID�� 3���� �̸� �Դϴ�." << endl;
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
				cout << "ID�� ���ڳ� ������ �ƴմϴ�." << endl;
				system("pause");
				break;
			}
		}
	}
	a = false;
	while (a == false || b == false)
	{
		system("cls");
		cout << "��й�ȣ �Է� ([8���� �̻�] AND [����] AND [���� ����]) :" << endl;
		cin >> M->PW;
		Limit = M->PW.length();
		if (Limit < 8)
		{
			cout << "Password�� 8���� �̸� �Դϴ�." << endl;
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
			cout << "Password�� ���ڰ� ���ԵǾ����� �ʽ��ϴ�." << endl;
			system("pause");
			continue;
		}
		else if (b == false)
		{
			cout << "Password�� ������ ���ԵǾ����� �ʽ��ϴ�." << endl;
			system("pause");
			continue;
		}
		cout << "��й�ȣ Ȯ�� :" << endl;
		cin >> ConfirmPW;
		if (M->PW != ConfirmPW)
		{
			cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
			system("pause");
		}
	}
	system("cls");
	cout << "�г��� �Է� :" << endl;
	cin >> M->Name;
	cout << "���� �Է� :" << endl;
	cin >> M->Age;
	cout << "�޴��� ��ȣ �Է� :" << endl;
	cin >> M->PN;
	cout << "ȸ������ ����!! ���ϸ��� 1000�� ���" << endl;
	(*MCount)++;
	M->Mileage = 1000;
}

void Show(Member* M)
{
	cout << "=======ȸ�� ����=======" << endl;
	cout << "ID : " << M->ID << "\t �г��� : " << M->Name << endl;
	cout << "����: " << M->Age << "\t �޴��� ��ȣ : " << M->PN << endl;
	cout << "���ϸ��� : " << M->Mileage << endl;
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
		cout << "1.�г��� ����" << endl;
		cout << "2.���� ����" << endl;
		cout << "3.�޴��� ��ȣ ����" << endl;
		cout << "4.���ư���" << endl;
		cout << "�Է� :" << endl;
		cin >> Select;
		system("cls");
		switch (Select)
		{
		case 1:
			cout << "���� �г���: " << Mem->Name << endl;
			cout << "������ �г��� �Է�: " << endl;
			cin >> str;
			Mem->Name = str;
			break;
		case 2:
			cout << "���� ����: " << Mem->Name << endl;
			cout << "������ ���� �Է�: " << endl;
			cin >>Num;
			Mem->Age = Num;
			break;
		case 3:
			cout << "���� ��ȣ: " << Mem->Name << endl;
			cout << "������ ��ȣ �Է�: " << endl;
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
		cout << "  1. ȸ�� ����" << endl;
		cout << "  2. ȸ�� ���� ����" << endl;
		cout << "  3. �α׾ƿ�" << endl;
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
		cout << "���̵� �Է� :" << endl;
		cin >> ID;
		cout << "��й�ȣ �Է� :" << endl;
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
	cout << "=====Login=====(ȸ����[" << MCount << "��])" << endl;
	cout << "\t1. ȸ�� ����" << endl;
	cout << "\t2. �α���" << endl;
	cout << "\t3. ����" << endl;
	cout << "�Է� :" << endl;
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
				cout << "�߸��� �����Դϴ�." << endl;
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



