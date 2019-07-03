typedef struct letterLogsInfo
{
	char str[99];
	int idx;
}LETTERINFO;

bool isDigit(char c)
{
	return ('0' <= c && c <= '9') ? true : false;
}

int compare(const void *a, const void *b)
{
	LETTERINFO *s1 = (LETTERINFO *)a;
	LETTERINFO *s2 = (LETTERINFO *)b;

	int ret = strcmp(s1->str, s2->str);
	return (ret == 0) ? (s2->idx - s1->idx) : ret;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** reorderLogFiles(char ** logs, int logsSize, int* returnSize)
{
	// Record the digit-log index
	int *digitLogRecord = malloc(logsSize*sizeof(int));
	int digitLogCtr = 0;
	// Record the letter-logs info
	LETTERINFO *letterLogInfo = calloc(logsSize, sizeof(LETTERINFO));
	int letterLogCtr = 0;
	for (int logsIdx = 0; logsIdx < logsSize; logsIdx++)
	{        
		int curLogLen = strlen(logs[logsIdx]);
		int i = 0;
		while (logs[logsIdx][i] != ' ')
		{
			i++;
		}
		if (isDigit(logs[logsIdx][i+1]))
		{
			digitLogRecord[digitLogCtr] = logsIdx;
			digitLogCtr++;
		} else
		{
			strcpy(letterLogInfo[letterLogCtr].str, &(logs[logsIdx][i+1]));
			letterLogInfo[letterLogCtr].idx = logsIdx;
			letterLogCtr++;

		}
	}

	qsort(letterLogInfo, letterLogCtr, sizeof(LETTERINFO), compare);

	char **ret = malloc(sizeof(char*)*logsSize);
	*returnSize = logsSize;
	int x;
	for (x = 0; x < letterLogCtr; x++)
	{
		ret[x] = calloc(101, sizeof(char));
		strcpy(ret[x], logs[letterLogInfo[x].idx]);
	}
	for (int i = 0; i < digitLogCtr; i++)
	{
		ret[i+x] = calloc(101, sizeof(char));
		strcpy(ret[i+x], logs[digitLogRecord[i]]);
	}

	free(letterLogInfo);
	return ret;

}

