
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArrayByParity(int* A, int ASize, int* returnSize)
{
	int oddIdx = ASize-1;
	for (int i = 0; i < oddIdx; i++)
	{        
		if (A[i] % 2 != 0)
		{
			int tmp = A[i];
			A[i] = A[oddIdx];
			A[oddIdx] = tmp;
			oddIdx--;
			i--;
		}
	}

	*returnSize = ASize;
	return A;
}

