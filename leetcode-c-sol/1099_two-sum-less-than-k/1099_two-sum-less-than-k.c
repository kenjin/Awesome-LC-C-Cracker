
int twoSumLessThanK(int* A, int ASize, int K)
{
	int max = -1;
	for (int i = 0; i < ASize; i++)
	{
		for (int j = i+1; j < ASize; j++)
		{
			int tmp = A[i] + A[j];
			if (tmp < K)
			{
				max = max > tmp ? max : tmp;
			}
		}
	}

	return max;
}

