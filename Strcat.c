#include <stdio.h>
#include <string.h>

void Strcat(char* str, char add[])
{
	int Start = strlen(str);
	int End = strlen(add);
	for (int i = 0; i < End; i++)
		str[Start + i] = add[i];
	str[Start + End] = NULL;
}

void main()
{
	char str[50];
	printf("���ڿ��� �Է��Ͻÿ� :");
	scanf("%s", str);
	Strcat(str, "friend");
	printf("������ ���ڿ� :%s", str);
}