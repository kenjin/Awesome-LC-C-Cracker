#define MAX_SIGNED_INT_32_LEN   (10)

bool smallestFactorizationHelper(int a, int retCtr, char *ret, char *max, int *maxLen)
{
	// Fill the answer and check the min
	if (a < 10)
	{
		if (a != 1 || retCtr == 0)
		{
			ret[retCtr++] = a + '0';            
		}
		ret[retCtr] = 0;
		if (retCtr > MAX_SIGNED_INT_32_LEN)
		{
			return false;
		}
		if (retCtr < *maxLen || (retCtr == *maxLen && strncmp(ret, max, retCtr) < 0))
		{
			*maxLen = retCtr;
			strcpy(max, ret);
		}
		return true;
	}

	// Over the 32-bit signed int, return false
	if (retCtr == MAX_SIGNED_INT_32_LEN)
	{
		return false;
	}

	int tmp;
	int found = 0;
	for (int i = 2; i < 10; i++)
	{
		if (a % i != 0)
		{
			continue;
		}
		ret[retCtr] = i + '0';
		if (smallestFactorizationHelper(a/i, retCtr+1, ret, max, maxLen))
		{
			found = 1;
		}
	}
	if (!found)
	{
		return false;
	}

	return true;
}


int smallestFactorization(int a)
{
	// 32-bit max signed int = 2147483647 
	int maxLen = MAX_SIGNED_INT_32_LEN;
	char *res = calloc(maxLen+2, sizeof(char));
	char *max = calloc(maxLen+2, sizeof(char));    
	strcpy(max, "2147483647");

	int val = 0;
	if (smallestFactorizationHelper(a, 0, res, max, &maxLen))
	{
		val = atoi(max);
	}

	free(res);
	free(max);
	return (val == 2147483647 ? 0 : val);
}

