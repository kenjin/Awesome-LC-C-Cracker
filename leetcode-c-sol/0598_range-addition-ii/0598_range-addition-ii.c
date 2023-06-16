#define MIN(a, b) (a < b ? a : b)

int maxCount(int m, int n, int** ops, int opsSize, int* opsColSize)
{
	int minM = m;
	int minN = n;
	for (int x = 0; x < opsSize; x++)
	{
		minM = MIN(minM, ops[x][0]);
		minN = MIN(minN, ops[x][1]);
	}

	return minM * minN;
}

