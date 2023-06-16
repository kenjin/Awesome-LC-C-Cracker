/**
50. Pow(x, n) [M]
Ref: https://leetcode.com/problems/powx-n/

 */

double pow_recursive(double x, int n)
{
	if (n == 0)
	{
		return 1;
	}

	if ((n & 0x1))
	{
		return pow_recursive(x, n/2) * pow_recursive(x, n/2) * x;
	} else
	{
		return pow_recursive(x, n/2) * pow_recursive(x, n/2);
	}
}

double myPow(double x, int n)
{
	int sign = 1;
	int minInt = 0;
	if (n < 0)
	{
		sign = 0;
		/* INT_MIN: corner case */
		if (n == INT_MIN)
		{
			n++;
			minInt = 1;
		}    
		n = n * (-1);
	}

	double sum = pow_recursive(x, n);    
	if (minInt)
	{
		sum *= x;
	}

	if (!sign)
	{
		return 1/sum;
	} else
	{
		return sum;
	}
}
