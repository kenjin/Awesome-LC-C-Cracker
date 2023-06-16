int subarraysDivByK(int* A, int ASize, int K)
{
	int *set = calloc(K, sizeof(int));    
	int tmp = 0, ret = 0;
	for (int i = 0; i < ASize; i++)
	{        
		tmp = (tmp + A[i]) % K;
		tmp = (tmp < 0 ? tmp + K : tmp);
		set[tmp] ++;
	}

	for (int i = 0 ; i < K; i++)
	{
		if (set[i] > 1)
		{
			ret += (set[i]*(set[i]-1)) / 2;
		}
	}

	// pick itself
	ret += set[0];

	free(set);
	return ret;            
}
