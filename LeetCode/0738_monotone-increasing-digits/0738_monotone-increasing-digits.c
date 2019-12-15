
int monotoneIncreasingDigits(int N)
{
	int tmp = N, nineSum = 9, base = 10;
	int pre = tmp % 10;
	int sum = pre;
	tmp /= 10;
	while (tmp)
	{
		int cur = tmp % 10;        
		sum += base*cur;

		if (cur > pre)
		{
			int add = base*(cur-1);
			N = N - sum + base*(cur-1) + nineSum;
			sum = base*(cur-1) + nineSum;
			pre = cur-1;
		} else
		{
			pre = cur;
		}

		tmp /= 10;
		base *= 10;
		nineSum = nineSum*10+9;
	}

	return N;
}

