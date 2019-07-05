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
	printf("문자열을 입력하시오 :");
	scanf("%s", str);
	Strcat(str, "friend");
	printf("수정된 문자열 :%s", str);
}