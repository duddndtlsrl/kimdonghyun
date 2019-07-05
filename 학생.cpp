#include<iostream>
#include<string>
using namespace std;
#define MAX 10

//void ArrInt()
//{
//	int tmp;
//	int *Int = new int[5];
//	for (int i = 0; i < 5; i++)
//	{
//		cout << i + 1 << "��° ���� :";
//		cin >> Int[i];
//	}
//
//	cout << "\n �������� ������" << endl;
//	cout << "================" << endl;
//	for (int i = 0; i < 5; i++)
//	{
//		cout << i + 1 << "��° ���� : " << Int[i] << endl;
//	}
//	cout << "================" << endl << endl;;
//
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = i + 1; j < 5; j++)
//		{
//			if (Int[i] > Int[j])
//			{
//				tmp = Int[i];
//				Int[i] = Int[j];
//				Int[j] = tmp;
//			}
//		}
//	}
//
//	cout << "�������� ������" << endl;
//	cout << "================" << endl;
//	for (int i = 0; i < 5; i++)
//	{
//		cout << i + 1 << "��° ���� : " << Int[i] << endl;
//	}
//	cout << "================" << endl;
//
//	delete[] Int;
//}

typedef struct Student
{
	string Name;
	char Result;
	int Age;
	int Grade;
	int Num;
	int Score[3];
	float Avg;
}student;

void Menu(int StCount)
{
	int Select;
	cout << "===�л���������===(�л��� : " << StCount << "��)" << endl;
	cout << "   1. �л����" << endl;
	cout << "   2. �л����� ����" << endl;
	cout << "   3. �л� �˻�" << endl;
	cout << "   4. ��޺� ����" << endl;
	cout << "   5. �г⺰ ����" << endl;
	cout << "   6. ����" << endl;
	cout << "�Է� :" << endl;
}

void Register(student* S, int* SC)
{
	cout << "=====" << *(SC)+1 << "��° �л�=====" << endl;
	cout << "�̸� :" << endl;
	cin >> S->Name;
	cout << "���� :" << endl;
	cin >> S->Age;
	while (1)
	{
		cout << "�г�(1~3) :" << endl;
		cin >> S->Grade;
		if (S->Grade > 3)
			cout << "�г��� �ٽ� �Է����ֽʽÿ�." << endl;
		else
			break;
	}
	cout << "�������� :" << endl;
	cin >> S->Score[0];
	cout << "�������� :" << endl;
	cin >> S->Score[1];
	cout << "�������� :" << endl;
	cin >> S->Score[2];
	S->Avg = (S->Score[0] + S->Score[1] + S->Score[2]) / 3.0;
	if (90 <= S->Avg && S->Avg <= 100)
		S->Result = 'A';
	else if (80 <= S->Avg && S->Avg <= 89)
		S->Result = 'B';
	else if (70 <= S->Avg && S->Avg <= 79)
		S->Result = 'C';
	else if (60 <= S->Avg && S->Avg <= 69)
		S->Result = 'D';
	else
		S->Result = 'F';
	S->Num = ++(*SC);
}

void Show(student* S)
{
		cout << "======" << S->Num << "��° �л�======" << endl;
		cout << "�̸� : " << S->Name << endl;
		cout << "���� : " << S->Age << "��" << endl;;
		cout << "�г� : " << S->Grade << "�г�" << endl;
		cout << "�������� : " << S->Score[0] << endl;
		cout << "�������� : " << S->Score[1] << endl;
		cout << "�������� : " << S->Score[2] << endl;
		cout << "�հ� ���� :" << (S->Score[0] + S->Score[1] + S->Score[2]) << "\t��� ���� :" << S->Avg << endl;
		cout << "��� :" << S->Result << endl;
		cout << "==================" << endl;
}

int Search(student* S[], int SC)
{
	string str;
	cout << "�̸� �Է� :" << endl;
	cin >> str;
	for (int i = 0; i < SC; i++)
	{
		if (S[i]->Name == str)
			return i;
	}
}

void ArrResult(student* S[], int SC)
{
	for (char i = 'A'; i < 'G'; i++)
	{
		if (i == 'E')
			continue;
		cout << "����������������" << i << " ��ަ���������������" << endl;
		for (int j = 0; j < SC; j++)
		{
			if (S[j]->Result == i)
				Show(S[j]);
		}
		cout << "����������������������������������" << endl;
	}
}

void ArrGrade(student* S[], int SC)
{
	for (int i = 1; i < 4; i++)
	{
		cout << "����������������" << i << " �г⦡��������������" << endl;
		for (int j = 0; j < SC; j++)
		{
			if (S[j]->Grade == i)
				Show(S[j]);
		}
		cout << "����������������������������������" << endl;
	}
}


void main()
{
	/*ArrInt();*/
	
	student* St[MAX];
	int StCount=0, Select, i;
	while (1)
	{
		system("cls");
		Menu(StCount);
		cin >> Select;
		system("cls");
		switch (Select)
		{
		case 1:
			if (StCount < MAX)
			{
				St[StCount] = new student;
				Register(St[StCount], &StCount);
			}
				break;
		case 2:
			for(int i=0; i<StCount; i++)
				Show(St[i]);
			system("pause");
			break;
		case 3:
				i = Search(St, StCount);
				if(i >= 0)
					Show(St[i]);
			else
				cout << "�ش� �л��� �����ϴ�." << endl;
			system("pause");
			break;
		case 4:
			ArrResult(St, StCount);
			system("pause");
			break;
		case 5:
			ArrGrade(St, StCount);
			system("pause");
			break;
		case 6:
			for (int i = 0; i < StCount; i++)
				delete St[i];
			cout << "�Ҵ� ���� �Ϸ�" << endl;
			system("pause");
			return;
		}
	}

}
