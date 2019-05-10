/**

28. Implement strStr() [E]

Ref: https://leetcode.com/problems/implement-strstr/

 */

int strStr(char * haystack, char * needle)
{
	if (needle == NULL)
	{
		return 0;
	}

	/* Implement strlen() */
	int lenA = 0, lenB = 0;
	while (haystack[lenA] != '\0')
	{
		lenA++;
	}
	while (needle[lenB] != '\0')
	{
		lenB++;
	}

	for (int i = 0; (i+lenB-1) < lenA; i++)
	{
		int fail = 0;
		for (int j = 0; j < lenB; j++)        
		{
			if (haystack[i+j] != needle[j])
			{
				fail = 1;
				break;   
			}            
		}
		if (!fail)
		{
			return i;
		}
	}
	return -1;
}
