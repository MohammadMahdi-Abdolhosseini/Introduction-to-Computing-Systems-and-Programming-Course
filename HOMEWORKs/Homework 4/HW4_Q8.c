#include <stdio.h>
/****************************************
//question 8:
//detect alphabet order.
*****************************************/
int alphabet_order_detector(char y[], char x[])
{
	for (int i = 0; i < 25; i++)
	{
		if (x[i] > y[i])
			return 2;
		if (x[i] < y[i])
			return 1;
	}
	return 0;
}
int main() {
	char x[25] = " ";
	gets(x);
	char y[25] = " ";
	gets(y);
	int r = alphabet_order_detector(y, x);
	printf("%d", r);
}