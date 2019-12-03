
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* prefixesDivBy5(int* A, int ASize, int* returnSize)
{
	bool *ret = malloc(sizeof(bool)*ASize);
	int sum = 0;
	for (int i = 0; i < ASize; i++)
	{
		sum *= 2;
		sum = (sum + A[i]) % 5;
		ret[i] = (sum % 5 == 0 ? true : false);

	}
	*returnSize = ASize;
	return ret;
}

