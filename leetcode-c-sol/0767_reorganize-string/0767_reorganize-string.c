typedef struct
{
	char c;
	int freq;
} CHARINFO;

char * reorganizeString(char * S)
{
	int charVisit[26];
	for (int i = 0; i < 26; i++)
	{
		charVisit[i] = -1;
	}
	CHARINFO record[26] = {0};
	int len = strlen(S);
	int recordCtr = 0;    
	int maxIdx = 0;
	for (int i = 0; i < len; i++)
	{
		int cur = charVisit[S[i] - 'a'];
		if (-1 == cur)
		{
			charVisit[S[i] - 'a'] = recordCtr;
			record[recordCtr].c = S[i];
			record[recordCtr].freq = 1;
			maxIdx = (record[maxIdx].freq > record[recordCtr].freq ? maxIdx : recordCtr);
			recordCtr++;
		} else
		{
			record[cur].freq ++;
			maxIdx = (record[maxIdx].freq > record[cur].freq ? maxIdx : cur);
		}
	}

	if (((len % 2 == 0) && record[maxIdx].freq > len/2) ||
			((len % 2 != 0) && record[maxIdx].freq > len/2+1))
	{
		S[0] = 0;
		return S;
	}

	// Fill even char
	int idx = 0;
	while (record[maxIdx].freq)
	{
		S[idx] = record[maxIdx].c;
		record[maxIdx].freq --;
		idx += 2;
	}    
	int fillCtr = 0;
	while (idx < len)
	{
		if (record[fillCtr].freq)
		{
			S[idx] = record[fillCtr].c;
		} else
		{
			fillCtr = (fillCtr+1) % (recordCtr+1);
			continue;            
		}
		record[fillCtr].freq--;
		idx += 2;
	}

	// Fill odd char
	idx = 1;
	while (idx < len)
	{
		if (record[fillCtr].freq)
		{
			S[idx] = record[fillCtr].c;
		} else
		{
			fillCtr = (fillCtr+1) % (recordCtr+1);
			continue;
		}
		record[fillCtr].freq--;
		idx += 2;
	}

	return S;
}

