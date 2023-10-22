#include <stdio.h>
/********************************************************
//question 10:
//Vigenere Cipher
*********************************************************/
int main() {
	char str[1000] = " ";
	gets(str);

	char key[20] = " ";
	gets(key);
	//int num = scanf_s("%[^\n]%*c", str);
	int j = 0;
	for (int i = 0; i < 1000; i++)
	{
		if (key[j] != NULL && j < 20)
		{
			if (str[i] != '.' && str[i] != ',' && str[i] != ' ' && str[i] != 0)
			{
				int k = key[j] - 97;
				str[i] -= k;
				if (str[i] < 97)
					str[i] += 26;
				j++;
			}
		}
		else
			j = 0, i--;

	}
	printf("%s\n", str);
}