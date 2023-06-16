int integerReplacement(int n)
{
	if (n == 1)
	{
		return 0;
	}

	if (n % 2)
	{
		int r1 = integerReplacement((n >> 1) + 1) + 2;
		int r2 = integerReplacement((n-1) >> 1) + 2;
		return (r1 < r2 ? r1 : r2);
	} else
	{
		return integerReplacement(n >> 1) + 1;
	}
}
