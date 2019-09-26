
void reverse(char *s, int head, int tail)
{
	while (head < tail)
	{
		char tmp = s[head];
		s[head] = s[tail];
		s[tail] = tmp;        
		head++;
		tail--;
	}
}

char * reverseStr(char * s, int k)
{
	int len = strlen(s);
	int i, ctr = 0;
	for (i = 0; i < len-k+1; i += 2*k)
	{
		reverse(s, i, i+k-1);
	}

	if (i < len)
	{
		reverse(s, i, len-1);
	}

	return s;
}


