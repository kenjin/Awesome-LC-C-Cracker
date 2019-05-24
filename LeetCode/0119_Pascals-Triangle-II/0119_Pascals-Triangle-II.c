/**
119. Pascal's Triangle II [E]

Given a non-negative index k where k ≤ 33, return the kth index row of the Pascal's triangle.
Note that the row index starts from 0.

 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getRow(int rowIndex, int* returnSize)
{
	int *ret = calloc((rowIndex+1), sizeof(int));
	*returnSize = rowIndex+1;
	ret[0] = 1;
	for (int i = 1; i <= rowIndex; i++) 
	{
		for (int j = i; j >= 1; j--) 
		{
			ret[j] += ret[j - 1];
		}
	}

	return ret;
}
