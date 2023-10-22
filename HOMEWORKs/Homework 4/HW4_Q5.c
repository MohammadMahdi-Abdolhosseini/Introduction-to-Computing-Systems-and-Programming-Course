#include <stdio.h>
/***************************************************
//question 5:
//insertion sort.
****************************************************/
int main() {
	int n;
	int sort[100] = { 0 };
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d", (sort + i));
	}

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (sort[i] < sort[j])
			{
				int r = sort[i];
				sort[i] = sort[j];
				sort[j] = r;
			}
		}
	}


	for (int i = 0; i < n; i++)
	{
		printf("%d ", sort[i]);
	}
}
