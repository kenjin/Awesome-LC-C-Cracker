
int checkFirstWindow(int *asciiSet, int checkLen, char *str)
{
	int ctr = 0;
	for (int i = 0; i < checkLen; i++)
	{
		int curIdx = str[i] - 'a';
		asciiSet[curIdx]--;
		if (asciiSet[curIdx] >= 0)
		{                        
			ctr++;
		}                
	}

	return ctr;
}

bool checkInclusion(char * s1, char * s2)
{
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	if (len1 > len2)
	{
		return false;
	}

	int asciiSet[26] = {0};
	while (*s1)
	{
		asciiSet[*s1 - 'a'] += 1;
		s1++;
	}

	// Check the window from the head of s2 string
	int ctr = checkFirstWindow(asciiSet, len1, s2);    
	if (ctr == len1)
	{
		return true;
	}
	// Sliding Window
	int head = 1;
	int tail = len1;
	while (tail < len2) 
	{
		int winDelIdx = s2[head-1] - 'a';
		int winTailIdx = s2[tail] - 'a';

		asciiSet[winDelIdx]++;
		if (asciiSet[winDelIdx] > 0)
		{
			ctr--;                
		}

		asciiSet[winTailIdx]--;
		if (asciiSet[winTailIdx] >= 0)
		{                        
			ctr++;
		}  

		if (ctr == len1)
		{
			return true;
		}
		head++;
		tail++;
	}

	return false;
}


