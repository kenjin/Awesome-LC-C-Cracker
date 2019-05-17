/**

22. Generate Parentheses [M]
Ref: https://leetcode.com/problems/generate-parentheses/

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
"((()))",
"(()())",
"(())()",
"()(())",
"()()()"
]

 */

#define MALLOC_SIZE_UNIT (500)
void getParenthesis(int left, int right, char *tmpStr, int index, char ***ret, int *returnSize)
{
	if (left > right)
	{
		return;
	}
	if (left == 0 && right == 0)
	{
		*returnSize += 1;
		if (*returnSize != 0 && *returnSize % MALLOC_SIZE_UNIT == 0)
		{
			*ret = (char**)realloc(*ret, sizeof(char*)*(*returnSize + MALLOC_SIZE_UNIT));
		}
		(*ret)[*returnSize-1] = (char*)calloc(index+1, sizeof(char));
		strcpy((*ret)[*returnSize-1], tmpStr);
		return;
	}

	if (left > 0)
	{
		tmpStr[index] = '(';
		getParenthesis(left-1, right, tmpStr, index+1, ret, returnSize);
	}
	if (right > 0)
	{
		tmpStr[index] = ')';
		getParenthesis(left, right-1, tmpStr, index+1, ret, returnSize);
	}
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** generateParenthesis(int n, int* returnSize)
{
	char *tmpStr = calloc(n*2+1, sizeof(char));
	char **ret = malloc(sizeof(char *)*MALLOC_SIZE_UNIT);
	*returnSize = 0;
	getParenthesis(n, n, tmpStr, 0, &ret, returnSize);    
	free(tmpStr);
	return ret;
}
