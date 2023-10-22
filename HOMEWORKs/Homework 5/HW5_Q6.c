#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SIZE_OF_STRING 50

char **get_n_string(int n)
{
	char **string = (char**)malloc(n * sizeof(char**));
	
	if (*string == NULL)
	{
		printf("out of memory");
		return 0;
	}

	for (int i = 0; i < SIZE_OF_STRING; i++)
	{
		string[i] = (char*)malloc(SIZE_OF_STRING * sizeof(char));
		if (string[i] == NULL)
		{
			printf("out of memory");
			return 0;
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		gets(*(string + i));
	}

	return string;
}

int main()
{
	int garbage;
	int n;
	scanf("%d", &n);
	getchar(&garbage);
	char **new_string;
	new_string = get_n_string(n);
	printf("*********************************\n");
	for (int i = 0; i < n; i++)
	{
		printf("%s\n", *(new_string + i));
	}

}