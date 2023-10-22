int convert_date(int m, int d)
{
	int k = -1;
	if (0 < m && m < 7)
	{
		if (d > 31 || d < 1)
			return k;
		else
		{
			k = 31;
			d += k * (m - 1);
			return d;
		}
	}
	if (6 < m && m < 13)
	{
		if (d > 30 || d < 1)
			return k;
		else
		{
			k = 30;
			d += k * (m - 6 - 1) + 31 * 6;
			return d;
		}
	}
	else
		return k;
}