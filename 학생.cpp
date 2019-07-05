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
//		cout << i + 1 << "번째 정수 :";
//		cin >> Int[i];
//	}
//
//	cout << "\n 오름차순 정렬전" << endl;
//	cout << "================" << endl;
//	for (int i = 0; i < 5; i++)
//	{
//		cout << i + 1 << "번째 정수 : " << Int[i] << endl;
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
//	cout << "오름차순 정렬후" << endl;
//	cout << "================" << endl;
//	for (int i = 0; i < 5; i++)
//	{
//		cout << i + 1 << "번째 정수 : " << Int[i] << endl;
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
	cout << "===학생정보관리===(학생수 : " << StCount << "명)" << endl;
	cout << "   1. 학생등록" << endl;
	cout << "   2. 학생정보 보기" << endl;
	cout << "   3. 학생 검색" << endl;
	cout << "   4. 등급별 보기" << endl;
	cout << "   5. 학년별 보기" << endl;
	cout << "   6. 종료" << endl;
	cout << "입력 :" << endl;
}

void Register(student* S, int* SC)
{
	cout << "=====" << *(SC)+1 << "번째 학생=====" << endl;
	cout << "이름 :" << endl;
	cin >> S->Name;
	cout << "나이 :" << endl;
	cin >> S->Age;
	while (1)
	{
		cout << "학년(1~3) :" << endl;
		cin >> S->Grade;
		if (S->Grade > 3)
			cout << "학년을 다시 입력해주십시오." << endl;
		else
			break;
	}
	cout << "국어점수 :" << endl;
	cin >> S->Score[0];
	cout << "영어점수 :" << endl;
	cin >> S->Score[1];
	cout << "수학점수 :" << endl;
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
		cout << "======" << S->Num << "번째 학생======" << endl;
		cout << "이름 : " << S->Name << endl;
		cout << "나이 : " << S->Age << "살" << endl;;
		cout << "학년 : " << S->Grade << "학년" << endl;
		cout << "국어점수 : " << S->Score[0] << endl;
		cout << "영어점수 : " << S->Score[1] << endl;
		cout << "수학점수 : " << S->Score[2] << endl;
		cout << "합계 점수 :" << (S->Score[0] + S->Score[1] + S->Score[2]) << "\t평균 점수 :" << S->Avg << endl;
		cout << "등급 :" << S->Result << endl;
		cout << "==================" << endl;
}

int Search(student* S[], int SC)
{
	string str;
	cout << "이름 입력 :" << endl;
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
		cout << "┌───────" << i << " 등급───────┐" << endl;
		for (int j = 0; j < SC; j++)
		{
			if (S[j]->Result == i)
				Show(S[j]);
		}
		cout << "└───────────────┘" << endl;
	}
}

void ArrGrade(student* S[], int SC)
{
	for (int i = 1; i < 4; i++)
	{
		cout << "┌───────" << i << " 학년───────┐" << endl;
		for (int j = 0; j < SC; j++)
		{
			if (S[j]->Grade == i)
				Show(S[j]);
		}
		cout << "└───────────────┘" << endl;
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
				cout << "해당 학생이 없습니다." << endl;
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
			cout << "할당 해제 완료" << endl;
			system("pause");
			return;
		}
	}

}
