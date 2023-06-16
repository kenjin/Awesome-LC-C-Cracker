
int lengthOfLongestSubstringTwoDistinct(char * s)
{    
	int sLen = strlen(s);
	if (sLen == 0)
	{
		return 0;
	}

	char pre = s[0];    
	char set[2] = {0};
	set[0] = pre;

	int ret = 0, repeat = 1, curCtr = 1, toggle = 0;
	for (int i = 1; i < sLen; i++)
	{
		if (s[i] != pre)
		{
			toggle ^= 1;
			// Find third distinct character
			if (set[toggle] != 0 && set[toggle] != s[i])
			{
				// Update result
				ret = (curCtr > ret ? curCtr : ret);                
				curCtr = repeat+1;                                
			} else
			{
				curCtr ++;
			}            
			set[toggle] = s[i];
			repeat = 1;
		} else
		{            
			curCtr++;
			repeat++;            
		}

		pre = s[i];
	}

	return (curCtr > ret ? curCtr : ret);
}

