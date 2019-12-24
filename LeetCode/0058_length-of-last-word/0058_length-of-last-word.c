

int lengthOfLastWord(char * s)
{
	int len = strlen(s);
	int ctr = 0;
	for (int i = len-1; i >= 0; i--)
	{
		if (s[i] == ' ')
		{
			if (ctr != 0)
			{
				break;    
			} else
			{
				continue;
			}
		}
		ctr++;
	}

	return ctr;
}


