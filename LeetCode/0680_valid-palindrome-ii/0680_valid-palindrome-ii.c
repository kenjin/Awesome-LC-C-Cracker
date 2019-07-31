bool validPalindromeHelper(char *s, int head, int tail, bool tolerance)
{
	while (head < tail)
	{        
		if (s[head] != s[tail])
		{
			if (tolerance)
			{  
				bool ret1 = validPalindromeHelper(s, head+1, tail, false);
				if (!ret1)
				{
					return validPalindromeHelper(s, head, tail-1, false);
				}
				return true;
			}
			return false;
		}
		head++;
		tail--;
	}
	return true;
}

bool validPalindrome(char * s)
{
	int len = strlen(s);
	return validPalindromeHelper(s, 0, len-1, true);
}

