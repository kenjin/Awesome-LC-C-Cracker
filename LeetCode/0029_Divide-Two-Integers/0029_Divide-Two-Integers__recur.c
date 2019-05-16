
/**
 *     32/3  
 *      3 (3 << 0)
 *      6 (3 << 1)
 *     12
 *     24
 *     48  => "48 > 32" => 32-24=8
 *
 *      8/3
 *      3
 *      6
 *     12  => "12 > 8" => 8-6=2
 *
 *      2/3  => "2 < 3" => return 
 *         
 */
int divideHelper(long divd, long divs)
{
	if (divd < divs)
	{
		return 0;
	}

	int shift = 0;
	long tmp = divs << (shift);
	while (tmp <= divd)
	{
		shift++;
		tmp = divs << shift;
	}

	divd = divd - (divs << (shift-1));
	return (1 << (shift-1)) + divideHelper(divd, divs);
}

long adjustSign(char *sign, long num)
{
	if (num < 0)
	{
		*sign ^= 1;
		num *= -1;
	}
	return num;
}

int divide(int dividend, int divisor)
{
	/* edge case */
	if (divisor == 0)
	{
		return INT_MIN;
	}
	if (dividend == INT_MIN)
	{
		if (divisor == 1)
		{
			return INT_MIN;
		} else if (divisor == -1)
		{
			return INT_MAX;
		}
	}
	/* use long type to avoid int overflow */
	long divd = (long)dividend;
	long divs = (long)divisor;

	/* negative case */
	char sign = 0;
	divd = adjustSign(&sign, divd);
	divs = adjustSign(&sign, divs);

	if (divs < 0)
	{
		sign ^= 1;
		divs *= -1;
	}

	int ret = divideHelper(divd, divs);

	return (sign == 0 ? ret : ret*(-1));
}
