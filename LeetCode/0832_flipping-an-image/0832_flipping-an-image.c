
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** flipAndInvertImage(int** A, int ASize, int* AColSize, int* returnSize, int** returnColumnSizes)
{
	*returnColumnSizes = malloc(sizeof(int)*ASize);
	*returnSize = ASize;    
	for (int i = 0; i < ASize; i++)
	{
		(*returnColumnSizes)[i] = AColSize[i];
		int head = 0;
		int tail = AColSize[i]-1;
		while (head < tail)
		{
			int tmp = A[i][head];
			A[i][head] = A[i][tail]^1;
			A[i][tail] = tmp^1;

			head++;
			tail--;
		}

		if (head == tail)
		{
			A[i][head] ^= 1;
		}
	}

	return A;
}

