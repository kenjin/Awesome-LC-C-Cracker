
int lengthLongestPath(char * input)
{
	int inputLen = strlen(input);
	int i = 0;
	int level = 1;
	int maxLen = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\n')
		{
			level++;
		}
		i++;
	}

	int *levelLenMap = calloc(level, sizeof(int));
	i = 0;
	int curLevel = 0;
	int nameLen = 0;
	bool isDotFile = false;
	while (1)
	{
		if (input[i] == '\t')
		{
			curLevel++;
			i++;
			continue;
		}

		// Check the file format
		if (input[i] == '.')
		{
			isDotFile = true;
		}

		if (input[i] == '\n' || input[i] == '\0')
		{
			if (isDotFile) // calculate abs file path
			{
				int tmpMax = (curLevel == 0 ? nameLen:
						levelLenMap[curLevel-1] + nameLen + 1);
				maxLen = (tmpMax > maxLen ? tmpMax : maxLen);
			} else // update level-len map
			{
				levelLenMap[curLevel] = (curLevel == 0 ? nameLen:
						levelLenMap[curLevel-1] + nameLen + 1);                
			}

			if (input[i] == '\0')
			{
				break;
			}
			isDotFile = false;
			curLevel = 0;
			nameLen = 0;
			i++;
			continue;
		}
		nameLen++;
		i++;
	}

	free(levelLenMap);
out:
	return maxLen;
}

