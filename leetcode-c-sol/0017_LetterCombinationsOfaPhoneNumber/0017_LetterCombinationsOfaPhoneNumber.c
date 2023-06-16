/**
  Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.

  A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.


Example:

Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:

Although the above answer is in lexicographical order, your answer could be in any order you want.

 */

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct phoneDict
{
	char *letter;
	int size;
};

void letterCombDFS(struct phoneDict *dict, char **ret, char *digits, int digLen, int index, int *returnSize, char *retEachStr)
{   
	if (index == digLen)
	{
		int curStrLen = strlen(retEachStr);
		char *res = calloc(curStrLen+1, sizeof(char)); // +1 ('\0')
		memcpy(res, retEachStr, curStrLen);        
		ret[*returnSize] = res;
		(*returnSize) += 1;
		return;
	}

	int i = 0;
	char *letter = dict[(*digits)-'0'].letter;

	while (letter[i] != 0 && i < 4)
	{
		retEachStr[index] = letter[i];
		letterCombDFS(dict, ret, digits+1, digLen, index+1, returnSize, retEachStr);        
		i++;
	}
}

char** letterCombinations(char* digits, int* returnSize) {
	struct phoneDict dict[] = {
		{.letter = "", .size = 0},
		{.letter = "", .size = 0},
		{.letter = "abc", .size = 3},
		{.letter = "def", .size = 3},
		{.letter = "ghi", .size = 3},
		{.letter = "jkl", .size = 3},
		{.letter = "mno", .size = 3},
		{.letter = "pqrs", .size = 4},
		{.letter = "tuv", .size = 3},
		{.letter = "wxyz", .size = 4},
	};

	int digLen = strlen(digits);
	int retLen = 1;
	if (digLen == 0 || digits == NULL)
	{
		*returnSize = 0;
		return NULL;
	}

	for (int x = 0; x < digLen; x++)
	{
		if (digits[x]-'0' < 2)
		{
			return NULL; // Input out of spec: Given a string containing digits from 2-9 inclusive
		}
		retLen *= dict[(digits[x]-'0')].size;
	}

	char **ret = (char**)malloc(sizeof(char*)*retLen);
	char *retEachStr = (char *)calloc((digLen+1), sizeof(char));    

	letterCombDFS(dict, ret, digits, digLen, 0, returnSize, retEachStr);

	free(retEachStr);
	return ret;
}

