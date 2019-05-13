/**

412. Fizz Buzz [E]
Ref: https://leetcode.com/problems/fizz-buzz/

 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void createStr(int ***ret, int *returnSize, char *str, int size)
{
	*returnSize += 1;
	(*ret)[(*returnSize)-1] = calloc(size, sizeof(char));
	strcpy((*ret)[(*returnSize)-1], str);    
}

char ** fizzBuzz(int n, int* returnSize)
{
	char **ret = malloc(sizeof(char*)*n);
	*returnSize = 0;
	for (int i = 1; i <= n; i++)
	{
		if (i % 15 == 0)
		{
			createStr(&ret, returnSize, "FizzBuzz", 9);
		} else if (i % 3 == 0)
		{
			createStr(&ret, returnSize, "Fizz", 5);
		} else if (i % 5 == 0)
		{
			createStr(&ret, returnSize, "Buzz", 5);
		} else
		{
			char chNum[12] = {0};
			sprintf(chNum, "%d", i);
			createStr(&ret, returnSize, chNum, strlen(chNum)+1);
		}
	}

	return ret;
}
