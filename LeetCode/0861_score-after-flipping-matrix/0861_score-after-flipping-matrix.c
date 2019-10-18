
int matrixScore(int** A, int ASize, int* AColSize)
{
	int colSize = AColSize[0];
	// Check the MSB of each element, we want to make 
	// sure that MSB of each element to be 1
	for (int i = 0; i < ASize; i++)
	{
		if (!A[i][0])
		{
			for (int k = 0; k < colSize; k++)
			{
				A[k] ^= 1;
			}       
		}
	}

	int sum = ASize;
	for (int j = 1; j < colSize; j++)
	{
		int tmp = 0;
		for (int x = 0; x < ASize; x++)
		{
			tmp += A[x][j];
		}
		sum *= 2;
		tmp = tmp > (ASize-tmp) ? tmp : ASize-tmp;
		sum += tmp;
	}

	return sum;
}

