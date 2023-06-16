#define HAS_ONE_SPACE(a, b) \
	(a - b == 2 || b - a == 2)

#define IS_CONSECUTIVE(a, b) \
	(a - b == 1 || b - a == 1)

#define SWAP(a, b)  \
	do {    \
		a ^= b; b ^= a; a ^= b; \
	} while(0)

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* numMovesStones(int a, int b, int c, int* returnSize)
{
	int v1 = a, v2 = b, v3 = c;

	// Sort input
	if (v1 > v2)
	{
		SWAP(v1, v2); 
	}
	if (v1 > v3)
	{
		SWAP(v1, v3);
	}
	if (v2 > v3)
	{
		SWAP(v2, v3);
	}

	*returnSize = 2;
	int *ret = malloc(sizeof(int)*2);
	// Min Step
	if (HAS_ONE_SPACE(v1, v2) || HAS_ONE_SPACE(v2, v3))
	{
		ret[0] = 1;
	} else
	{    
		ret[0] = 2;
		if (IS_CONSECUTIVE(v1, v2))
		{
			ret[0] -= 1;
		}    
		if (IS_CONSECUTIVE(v2, v3))
		{
			ret[0] -= 1;
		}
	}
	// Max step
	ret[1] = (v2-v1-1) + (v3-v2-1);

	return ret;
}

