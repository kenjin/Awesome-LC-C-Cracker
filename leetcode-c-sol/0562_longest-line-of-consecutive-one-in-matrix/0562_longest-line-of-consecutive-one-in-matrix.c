#define MAX(a, b) (a > b ? a : b);

int longestLine(int** M, int MSize, int* MColSize)
{
	if (MSize == 0)
	{
		return 0;
	}

	int max = 0;
	int colSize = MColSize[0];
	for (int i = 0; i < MSize; i++)
	{
		int ctr = 0;
		for (int j = 0; j < colSize; j++)
		{
			if (M[i][j])
			{
				ctr++;
				max = MAX(max, ctr);
			} else
			{
				ctr = 0;                                
			}
		}
	}

	for (int j = 0; j < colSize; j++)    
	{
		int ctr = 0;
		for (int i = 0; i < MSize; i++)
		{
			if (M[i][j])
			{
				ctr++;
				max = MAX(max, ctr);
			} else
			{
				ctr = 0;                                
			}
		}
	}

	for (int i = 0; i < MSize + colSize - 1; i++)
	{
		int ctr1 = 0, ctr2 = 0;
		for (int j = i; j >= 0; j--) 
		{
			if (i - j < MSize && j < colSize) 
			{
				if (M[i - j][j] == 1)
				{
					ctr1++;
					max = MAX(max, ctr1);
				} else 
				{
					ctr1 = 0;
				}
			}
			int t = MSize - 1 - i + j;
			if (t >= 0 && t < MSize && j < colSize ) 
			{
				if (M[t][j] == 1)
				{
					ctr2++;
					max = MAX(max, ctr2);
				} else 
				{
					ctr2 = 0;
				}
			}
		}
	}

	return max;
}

