#include <stdio.h>
#include <string.h>

int Strcmp(char str[], char str1[])
{
	int Limit, Flag;
	if (strlen(str) >= strlen(str1))
		Limit = strlen(str);
	else
		Limit = strlen(str1);
	for (int i = 0; i < Limit; i++)
	{
		if (str[i] == str1[i])
			Flag = 0;
		else if (str[i] > str1[i])
		{
			Flag = 1;
			break;
		}
		else
		{
			Flag = -1;
			break;
		}
	}
	return Flag;
}

void main()
{
	char str1[] = "Hello";
	char str2[10];
	printf("문자열을 입력하시오 :");
	scanf("%s", str2);
	if (Strcmp(str1, str2) == 0)
		printf("%s와 %s는 같은 문자열입니다.\n", str1, str2);
	else
		printf("%s와 %s는 다른 문자열입니다.\n", str1, str2);
}


