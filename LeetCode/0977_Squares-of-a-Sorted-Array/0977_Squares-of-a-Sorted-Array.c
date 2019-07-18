
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortedSquares(int* A, int ASize, int* returnSize)
{
	*returnSize = ASize;
	int *ret = malloc(sizeof(int)*ASize);
	int *tmp = malloc(sizeof(int)*ASize);

	int i = 0;
	while (i < ASize)
	{
		if (A[i] >= 0)
		{
			break;
		}
		tmp[i] = A[i];
		i++;
	}

	int ctr = 0;
	int posIdx = i;
	int negIdx = i-1;
	while (posIdx < ASize && negIdx >= 0)
	{
		int p = A[posIdx]*A[posIdx];
		int n = tmp[negIdx]*tmp[negIdx];
		if (n < p)
		{
			ret[ctr] = n;
			negIdx--;
		} else
		{
			ret[ctr] = p;
			posIdx++;
		}
		ctr++;   
	}
	while (posIdx < ASize)
	{
		ret[ctr] = A[posIdx]*A[posIdx];
		posIdx++;
		ctr++;  
	}
	while (negIdx >= 0)
	{
		ret[ctr] = tmp[negIdx]*tmp[negIdx];
		negIdx--;
		ctr++;  
	}
	free(tmp);
	return ret;
}

