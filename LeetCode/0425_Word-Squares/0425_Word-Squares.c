
void backtracking(char ** words, int wordsSize, char **record, int recordCtr,
		int edgeLen, char ****ret, int *returnSize, int **returnColumnSizes)
{
	if (recordCtr == edgeLen)
	{
		// Get word squares and update the result
		*ret = realloc(*ret, sizeof(char**)*(*returnSize+1));            
		(*ret)[*returnSize] = malloc(sizeof(char*)*edgeLen);
		for (int x = 0; x < edgeLen; x++)
		{
			(*ret)[*returnSize][x] = calloc(edgeLen+1, sizeof(char));
			strcpy((*ret)[*returnSize][x], record[x]);                                
		}
		*returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*(*returnSize+1));
		(*returnColumnSizes)[*returnSize] = edgeLen;
		*returnSize += 1; 

		return;
	}
	for (int i = 0; i < wordsSize; i++)
	{

		char found = 1;
		for (int j = 0; j < recordCtr; j++)
		{
			if (words[i][j] != record[j][recordCtr])
			{
				found = 0;
				break;
			}
		}

		if (found)
		{
			record[recordCtr] = words[i];
			backtracking(words, wordsSize, record, recordCtr+1,
					edgeLen, ret, returnSize, returnColumnSizes);  
		}
	}
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** wordSquares(char ** words, int wordsSize, int* returnSize, int** returnColumnSizes)
{
	int edgeLen = strlen(words[0]);
	// Init the result strings memory
	char ***ret = malloc(sizeof(char **));
	*returnColumnSizes = malloc(sizeof(int));
	*returnSize = 0;
	// Word length is at least 1 and at most 5.
	char *record[5];
	for (int i = 0; i < wordsSize; i++)
	{
		int recordCtr = 1;
		record[0] = words[i];               
		backtracking(words, wordsSize, record, recordCtr, edgeLen, &ret, returnSize, returnColumnSizes);
	}

	return ret;
}
