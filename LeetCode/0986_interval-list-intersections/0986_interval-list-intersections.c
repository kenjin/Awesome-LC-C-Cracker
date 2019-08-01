bool isIntersection(int *dst, int *src)
{
	if ((dst[0] <= src[0] && src[0] <= dst[1]) ||
			(dst[0] <= src[1] && src[1] <= dst[1]))
	{
		return true;
	}
	return false;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** intervalIntersection(int** A, int ASize, int* AColSize, int** B, int BSize, int* BColSize, int* returnSize, int** returnColumnSizes)
{
	int memSizeUnit = ASize+BSize;
	int **ret = malloc(sizeof(int *)*memSizeUnit);
	*returnColumnSizes = malloc(sizeof(int)*memSizeUnit);

	int idxA = 0, idxB = 0, retCtr = 0;
	while (idxA < ASize && idxB < BSize)
	{
		// Find intersection
		if (isIntersection(A[idxA], B[idxB]) || isIntersection(B[idxB], A[idxA]))
		{
			// Add new intersection
			ret[retCtr] = malloc(sizeof(int)*2);
			(*returnColumnSizes)[retCtr] = 2;
			ret[retCtr][0] = (A[idxA][0] > B[idxB][0] ? A[idxA][0] : B[idxB][0]);
			ret[retCtr][1] = (A[idxA][1] < B[idxB][1] ? A[idxA][1] : B[idxB][1]);

			// Update input
			if (ret[retCtr][1]+1 <= A[idxA][1])
			{
				A[idxA][0] = ret[retCtr][1]+1;
			} else
			{
				idxA++;
			}
			if (ret[retCtr][1]+1 <= B[idxB][1])
			{
				B[idxB][0] = ret[retCtr][1]+1;
			} else
			{
				idxB++;
			}

			retCtr++;
			if (retCtr+1 % memSizeUnit == 0)
			{
				ret = realloc(ret, sizeof(int *)*(retCtr+memSizeUnit));
				(*returnColumnSizes) = realloc(*returnColumnSizes, sizeof(int)*(retCtr+memSizeUnit));
			}            
		} else
		{
			// If no intersection in this round, choose the smaller one to increase the index            
			if (A[idxA][1] <= B[idxB][0])
			{
				idxA++;
			} else
			{
				idxB++;
			}
		}
	}

	*returnSize = retCtr;
	return ret;
}

