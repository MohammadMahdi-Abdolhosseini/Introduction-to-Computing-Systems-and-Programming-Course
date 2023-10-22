int factorial(int x)
{
	int a = 1;
	int b = x;
	for (int i = 0; i < x; i++)
	{
		a *= b;
		b--;
	}
	return a;
}
float calculate_sum_of_sequence(int n)
{
	float result = 1;
	for (int i = 2; i < n + 1; i++)
	{
		float k;
		int r = i % 2;
		if (r == 0)
			k = -1;
		else
			k = 1;
		result += k / factorial(i);
	}
	return result;
}