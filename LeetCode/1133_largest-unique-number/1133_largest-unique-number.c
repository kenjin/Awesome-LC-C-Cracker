
int largestUniqueNumber(int* A, int ASize)
{
	int record[1001] = {0};    
	int max = -1, min = 1001;        
	for (int i = 0; i < ASize; i++)
	{
		record[A[i]] ++;        
		max = max > A[i] ? max : A[i];
		min = min < A[i] ? min : A[i];
	}

	int ret = -1, cur = max;
	while (cur >= min)
	{
		if (record[cur] == 1)
		{
			ret = cur;
			break;
		}
		cur--;
	}

	return ret;
}

