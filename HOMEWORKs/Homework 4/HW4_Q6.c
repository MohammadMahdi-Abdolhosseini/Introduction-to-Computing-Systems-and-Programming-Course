#include <stdio.h>
/**************************************************************
//question 6:
//caesar cipher decoder with K letters earlier of the alphabet.
**************************************************************/
int main() {
	char str[1000] = " ";
	gets(str);
	//int num = scanf_s("%[^\n]%*c", str);
	int k;
	scanf_s("%d", &k);
	for (int i = 0; i < 100; i++)
	{
		if (str[i] != '.' && str[i] != ',' && str[i] != ' ' && str[i] != 0)
		{
			str[i] -= k;
			if (str[i] < 97)
				str[i] += 26;
		}
	}
	printf("%s", str);
}