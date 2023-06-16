#define MALLOC_UNIT 10

char* reverseString(char *s)
{
	int head = 0, tail = strlen(s)-1;
	while (head < tail)
	{
		char tmp = s[head];
		s[head] = s[tail];
		s[tail] = tmp;

		head++;
		tail--;
	}

	return s;
}

char* convertToTitle(int n)
{
	char *ret = calloc(MALLOC_UNIT, sizeof(char));
	int i = 0;
	while (n > 0) 
	{
		int rem = n % 26;
		if (rem == 0) 
		{
			n = n / 26 - 1;
			ret[i] = 'Z';
			i++;
		} else 
		{
			n = n / 26;
			ret[i] = 'A' + rem - 1;
			i++;
		}
	}    

	ret = reverseString(ret);
	return ret;
}


