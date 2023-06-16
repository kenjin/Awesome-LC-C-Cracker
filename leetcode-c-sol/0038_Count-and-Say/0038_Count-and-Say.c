/*
 
38. Count and Say [E]
Ref: https://leetcode.com/problems/count-and-say/

 */

#define MALLOC_SIZE_UNIT (8000)

char * countAndSay(int n)
{
	char *base[6] = {"", "1", "11", "21", "1211", "111221"};

	if (n >= 1 && n <= 5)
	{
		return base[n];
	}
	char *ret = calloc(MALLOC_SIZE_UNIT, sizeof(char));
	char *str = calloc(MALLOC_SIZE_UNIT, sizeof(char));
	strcpy(str, base[5]);
	for (int i = 6; i <= n; i++)
	{
		memset(ret, 0, MALLOC_SIZE_UNIT*sizeof(char));
		int retSize = 0;
		int len = strlen(str);
		int ctr = 1, x;
		for (x = 1; x < len; x++)
		{
			if (str[x] != str[x-1])
			{
				ret[retSize] = ctr +'0';
				ret[retSize+1] = str[x-1];
				ctr = 1;
				retSize += 2;
			} else
			{
				ctr++;
			}
		}
		ret[retSize] = ctr +'0';
		ret[retSize+1] = str[x-1];

		strcpy(str, ret);
		str[retSize+2] = '\0';
	}
	free(str);
	return ret;
}
