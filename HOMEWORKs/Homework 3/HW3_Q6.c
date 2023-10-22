void print_rhombus(int n)
{
	for (int i = 1; i < n + 2; i++)//line i=1 to n+1
	{
		int space = 0, star = 0;
		while (space < n + 1 - i)//print space (" ") n+1-i times in line i
		{
			printf(" ");
			space++;
		}
		while (star < 2 * i - 1)//print star ("*") 2*i-1 times in line i
		{
			printf("*");
			star++;
		}
		printf("\n");
	}
	for (int j = n + 2; j < 2 * n + 2; j++)//line j=n+2 to 2*n+1
	{
		int space = 0, star = 0;
		while (space < j - (n + 1))//print space (" ") j-(n+1) times in line j
		{
			printf(" ");
			space++;
		}
		while (star < -2 * j + 4 * n + 3)//print star ("*") -2*j+4*n+3 times in line j
		{
			printf("*");
			star++;
		}
		printf("\n");
	}
}