
bool binarySearch(long head, long tail, long target)
{
	while (head < tail)
	{
		long mid = head + (tail-head)/2;
		long res = mid*mid;
		if (res == target)
		{
			return true;
		} else if (res < target)
		{
			head = mid+1;
		} else
		{
			tail = mid;
		}                
	}
	return false;
}

bool judgeSquareSum(int c)
{
	if (c <= 2)
	{
		return true;
	}

	for (long a = 0; a*a <= c; a++)
	{
		int bSquare = c - (int)a*a;
		if (binarySearch((long)0, (long)bSquare, (long)bSquare))
		{
			return true;
		}
	}
	return false;
}


