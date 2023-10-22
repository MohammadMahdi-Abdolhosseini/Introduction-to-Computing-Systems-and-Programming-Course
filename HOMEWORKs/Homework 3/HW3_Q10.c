void prime_factors(int n)
{
	int r = 2;
	while (n > 1)
	{
		if (n%r == 0) {
			n /= r;
			printf("%d ", r);
		}
		while (r < n)
		{
			if (n%r != 0)
				r++;
			else
				break;
		}
	}
}