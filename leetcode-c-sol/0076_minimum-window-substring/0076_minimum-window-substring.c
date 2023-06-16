
char * minWindow(char * s, char * t)
{
	int asciiSet[128] = {0};
	int sLen = strlen(s);
	int tLen = strlen(t);
	while (*t)
	{
		asciiSet[*t] += 1;
		t++;
	}

	char *emptyStr = "";
	int head = 0, ctr = 0;
	int retHead = 0, retTail = 0, minLen = INT_MAX;
	for (int i = 0; i < sLen; i++)
	{
		asciiSet[s[i]] -= 1;
		if (asciiSet[s[i]] >= 0)
		{
			ctr ++;
		}
		while (ctr == tLen)
		{
			if ((i-head+1) < minLen)
			{
				minLen = i-head+1;
				retHead = head;
				retTail = i;
			}

			asciiSet[s[head]] += 1;
			if (asciiSet[s[head]] > 0)
			{
				ctr--;
			}
			head++;
		}
	}

	if (minLen == INT_MAX)
	{
		return emptyStr;
	} else
	{
		s[retTail+1] = 0;
		return &(s[retHead]);
	}
}


