
bool isPalindrome(int x)
{
	if (x < 0)
	{
		return false;
	}

	int divideBase = 1;
	int tmp = x;
	while (tmp/10)
	{
		tmp /= 10;
		divideBase *= 10;
	}

	while (divideBase > 1)
	{
		if ((x/divideBase) != (x%10))
		{
			return false;
		}
		x %= divideBase;
		x /= 10;
		divideBase /= 10*10;        
	}
	return true;
}

