#include <stdio.h>
/******************************************************
//question 9:
//names order.
******************************************************/
int main() {
	char name[100][25] = { ' ' };
	int n;
	scanf_s("%d", &n);
	n++;

	for (int i = 0; i < n; i++)
	{
		gets(name + i);
	}


	int r;

	for (int i = 2; i < n; i++)
	{
		for (int j = 1; j < i; j++)
		{
			for (int k = 0; k < 50; k++)
			{
				if (name[i][k] != name[j][k])
				{
					r = k;
					break;
				}
			}
			if (name[i][r] < name[j][r])
			{
				for (int ii = 0; ii < 50; ii++)
				{
					char x = name[i][ii];
					name[i][ii] = name[j][ii];
					name[j][ii] = x;
				}

			}
		}
	}


	for (int i = 0; i < n; i++)
	{
		printf("%s\n", (name + i));
	}
}