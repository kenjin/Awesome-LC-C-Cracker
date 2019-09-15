#define MALLOC_UNIT 12

char * convertToTitle(int n)
{    
	char *ret = calloc(MALLOC_UNIT, sizeof(char));
	int retCtr = 0;
	for (int i = 6; i >= 0; i--)
	{
		int base = pow(26, i);
		if (n/base > 0)
		{
			ret[retCtr] = n/base + 'A' - 1;
			n %= base;
		} else
		{
			if (retCtr > 0 && ret[retCtr-1] >= 'A')
			{
				ret[retCtr-1] -= 1;
				ret[retCtr] = 'Z';
			} else
			{ 
				ret[retCtr] = 'A' - 1;
			} 

		}
		retCtr++;
	}

	for (int i = 0; i < retCtr; i++)
	{
		if (i > 0 && ret[i-1] >= 'A' && ret[i] < 'A')
		{
			ret[i-1] -= 1;
			ret[i] = 'Z';
		}
	}

	int start = 0;
	for (int i = 0; i < retCtr; i++)
	{
		if (ret[i] >= 'A')
		{
			start = i;
			break;
		}
	}
	return &(ret[start]);
}


