
int balancedStringSplit(char * s)
{
	int ret = 0;
	int balancedCtr = 0;
	while (*s)
	{
		if (*s == 'R')
		{
			balancedCtr++;
		} else
		{
			balancedCtr--;
		}

		if (balancedCtr == 0)
		{
			ret++;
		}
		s++;
	}

	return ret;
}

