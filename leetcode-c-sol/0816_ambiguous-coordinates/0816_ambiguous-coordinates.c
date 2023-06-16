
void addResult(char *str1, char *str2, char ***ret, int *retSize)
{
	*ret = realloc(*ret, sizeof(char *)*(*retSize + 1));
	(*ret)[*retSize] = calloc(20, sizeof(char));
	sprintf((*ret)[*retSize], "(%s, %s)", str1, str2);
	*retSize += 1;
}

void decimalPointsHandler(char *s1, char *s2, char *xStr, char ***ret, int *retSize)
{
	// Use xStr pointer to know which string(x-axis or y-axis) we need to process
	char *curStr = (xStr == NULL ? s1 : s2);    
	int len = strlen(curStr);

	// non decimal point case
	if ((*curStr == '0' && len == 1) || *curStr != '0')
	{
		if (xStr == NULL)
		{
			decimalPointsHandler(s1, s2, curStr, ret, retSize);
		} else
		{
			addResult(xStr, curStr, ret, retSize);
		}
	}
	// use decimal point case
	char *tmp = calloc(len+2, sizeof(char));
	tmp[0] = curStr[0];
	if (curStr[len-1] != '0')
	{    
		for (int i = 1; i < len; i++)
		{
			tmp[i] = '.';
			strcpy(&(tmp[i+1]), &(curStr[i]));     
			if ((tmp[0] == '0' && tmp[1] == '.') ||
					(tmp[0] != '0'))
			{
				if (xStr == NULL)
				{
					decimalPointsHandler(s1, s2, tmp, ret, retSize);
				} else
				{
					addResult(xStr, tmp, ret, retSize);
				}
			}
			tmp[i] = curStr[i];
		}
	}
	free(tmp);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** ambiguousCoordinates(char * S, int* returnSize)
{
	int len =strlen(S);
	S[len-1] = 0;

	char **ret = malloc(sizeof(char *));
	*returnSize = 0;

	char *coordinate = calloc(len+1, sizeof(char));
	strcpy(coordinate, S);
	// handle commas
	for (int i = 1; i < len-2; i++)
	{        
		coordinate[i+1] = 0;
		// Handle decimal point
		decimalPointsHandler(&(coordinate[1]), &(S[i+1]), NULL, &ret, returnSize);
		coordinate[i+1] = S[i+1];
	}
	free(coordinate);
	return ret;
}

