#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include<time.h>
#define MAX 10

typedef struct Player
{
	char Name[10];
	int Num;
	int Att;
	int CurrHp;
	int MaxHp;
	int CurrExp;
	int MaxExp;
	int GetExp;
	int Lev;
}Player;

int ECount = 1;
int EMax;

void SaveCheck()
{
	printf("====Save====\n");
	char buf[256];
	FILE* f;
	for (int i = 1; i < 11; i++)
	{
		sprintf(buf, "SaveFile%d.txt",  i);
		f = fopen(buf, "r");
		printf("%d������ : (���� ���� : ", i);
		if (f == NULL)
			printf("X");
		else
		{
			printf("O");
			fclose(f);
		}
		printf(")\n");
	}
	printf("���� :");
}

void Default(Player* P_List[])
{
	FILE* f = fopen("Default.txt", "r");
	fscanf(f, "%d", &EMax);
	for(int i=0; i<=EMax; i++)
		P_List[i] = (Player*)malloc(sizeof(Player));
	fscanf(f, "%d%d%d%d%d%d%d%d", &P_List[0]->Num, &P_List[0]->Att, &P_List[0]->CurrHp, &P_List[0]->MaxHp, &P_List[0]->CurrExp, &P_List[0]->MaxExp, &P_List[0]->GetExp, &P_List[0]->Lev);
	for (int i = 1; i <= EMax; i++)
		fscanf(f, "%s%d%d%d%d%d%d%d%d", P_List[i]->Name, &P_List[i]->Num, &P_List[i]->Att, &P_List[i]->CurrHp, &P_List[i]->MaxHp, &P_List[i]->CurrExp, &P_List[i]->MaxExp, &P_List[i]->GetExp, &P_List[i]->Lev);
	fclose(f);
}

void Status(Player* P)
{
	printf("=====%s(%dLv)=====\n", P->Name, P->Lev);
	printf("���ݷ� = %d\t����� = %d/%d\n", P->Att, P->CurrHp, P->MaxHp);
	printf("����ġ = %d/%d\tGetExp : %d\n", P->CurrExp, P->MaxExp, P->GetExp);
}

void Battle(Player* P, Player* E)
{
	int PC, EC;
	while (1)
	{
		scanf("%d", &PC);
		if (PC > 2)
			printf("�߸��� Ŀ�ǵ��Դϴ�.");
		else
			break;
	}
		EC = rand() % 3;
		if (PC < EC)
		{
			P->CurrHp -= E->Att;
			printf("%s�� %d�� �������� �Ծ���!!", P->Name, E->Att);
			if (PC == 0 && EC == 2)
			{
				E->CurrHp -= P->Att;
				printf("%s�� %d�� �������� �Ծ���!!", E->Name, P->Att);
			}
		}
		else if (PC == EC)
			printf("����.");
		else if (PC > EC)
		{
			E->CurrHp -= P->Att;
			printf("%s�� %d�� �������� �Ծ���!!", E->Name, P->Att);
			if (PC == 2 && EC == 0)
			{
				P->CurrHp -= E->Att;
				printf("%s�� %d�� �������� �Ծ���!!", P->Name, E->Att);
			}
		}
	system("pause");
}

void LevUp(Player* P)
{
	int Att, Life;
	Att = rand() % 5 + 1;
	Life = rand() % 11 + 1;
	P->Lev++;
	P->Att += Att;
	P->MaxHp += Life;
	P->CurrHp = P->MaxHp;
}

int GetExp(Player* P, Player* E)
{
	if (P->CurrHp <= 0)
	{
		if (P->CurrExp == 0)
			return 1;
		E->CurrExp += P->CurrExp;
		P->CurrExp = 0;
		P->CurrHp = P->MaxHp;
		if (E->CurrExp >= E->MaxExp)
			LevUp(E);
	}
	else if (E->CurrHp <= 0)
	{
		P->CurrExp += E->GetExp;
		E->CurrHp = E->MaxHp;
		if (P->CurrExp >= P->MaxExp)
			LevUp(P);
	}
}

void Save(Player* P_List[])
{
	int Num;
	char buf[256];
	scanf("%d", &Num);
	sprintf(buf, "SaveFile%d.txt", Num);
	FILE* f = fopen(buf,"w");
	fprintf(f, "%s %d %d %d %d %d %d %d %d\n", P_List[0]->Name, P_List[0]->Num, P_List[0]->Att, P_List[0]->CurrHp, P_List[0]->MaxHp, P_List[0]->CurrExp, P_List[0]->MaxExp, P_List[0]->GetExp, P_List[0]->Lev);
	fprintf(f, "%d", ECount);
	for (int i = 1; i <= EMax; i++)
		fprintf(f, "%s %d %d %d %d %d %d %d %d", P_List[i]->Name, P_List[i]->Num, P_List[i]->Att, P_List[i]->CurrHp, P_List[i]->MaxHp, P_List[i]->CurrExp, P_List[i]->MaxExp, P_List[i]->GetExp, P_List[i]->Lev);
	fclose(f);
}

void Load(Player* P_List[])
{
	int Num;
	char buf[256];
	scanf("%d", &Num);
	sprintf(buf, "SaveFile%d.txt", Num);
	FILE* f = fopen(buf, "w");
	fscanf(f, "%s%d%d%d%d%d%d%d%d", P_List[0]->Name, &P_List[0]->Num, &P_List[0]->Att, &P_List[0]->CurrHp, &P_List[0]->MaxHp, &P_List[0]->CurrExp, &P_List[0]->MaxExp, &P_List[0]->GetExp, &P_List[0]->Lev);
	fscanf(f, "%d", ECount);
	for (int i = 1; i <= EMax; i++)
		fscanf(f, "%s%d%d%d%d%d%d%d%d", P_List[i]->Name, &P_List[i]->Num, &P_List[i]->Att, &P_List[i]->CurrHp, &P_List[i]->MaxHp, &P_List[i]->CurrExp, &P_List[i]->MaxExp, &P_List[i]->GetExp, &P_List[i]->Lev);
	fclose(f);
}

void main()
{
	Player* P_List[MAX];
	int Select, Num;
	int DengeonFlag = 1;
	srand(time(NULL));
	Default(P_List);
	printf("����� �̸���?");
	scanf("%s", P_List[0]->Name);
	while (1)
	{
		system("cls");
		printf("=====Dungeon=====\n");
		printf("   1.���� ����\n");
		printf("   2.Play ����\n");
		printf("   3.Save\n");
		printf("   4.Load\n");
		printf("   5.����\n");
		printf("   �Է� : ");
		scanf("%d", &Select);
		switch (Select)
		{
		case 1:
			system("cls");
			if (P_List[0]->Lev % 5 == 0)
				ECount++;
			printf("====���� �Ա�====\n");
			for (int i = 1; i <= ECount; i++)
				printf("%d.%d�� ���� : [%s]\n", i, i, P_List[i]->Name);
			printf("���� :");
			scanf("%d", &Num);
			DengeonFlag = 1;
			while(DengeonFlag = 1)
			{
				system("cls");
				if (GetExp(P_List[0], P_List[Num]) == 1)
				{
					printf("Game Over");
					system("pause");
					DengeonFlag = 0;
					continue;
				}
				Status(P_List[0]);
				Status(P_List[Num]);
				printf("\n%s �Է�\n", P_List[0]->Name);
				printf("���� : 0, ���� : 1, �� : 2\n�Է� :");
				Battle(P_List[0], P_List[Num]);
				GetExp(P_List[0], P_List[Num]);
			}
			break;
		case 2:
			system("cls");
			Status(P_List[0]);
			printf("\n\n\n====Enemy====\n");
			for (int i = 1; i <= EMax; i++)
				Status(P_List[i]);
			system("pause");
			break;
		case 3:
			system("cls");
			SaveCheck();
			Save(P_List);
			break;
		case 4:
			system("cls")
			SaveCheck();
			Load(P_List);
			break;
		case 5:
			return;
		}
	}
}