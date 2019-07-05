
bool isLegal(char c1, char c2)
{
	int n1 = (c1 - '0')*10;
	int n2 = c2 - '0';
	return (n1 + n2 > 26) ? false : true;    
}

int numDecodingsHelper(char *s, int idx, int len)
{
	if (s[idx] == '0')
	{
		return 0;
	}

	if (idx+1 >= len)
	{            
		return 1;
	}

	int ctr = 0;
	if (isLegal(s[idx], s[idx+1]))
	{
		ctr += numDecodingsHelper(s, idx+2, len);
	}
	ctr += numDecodingsHelper(s, idx+1, len);

	return ctr;
}


int numDecodings(char * s)
{
	int len = strlen(s);

	return numDecodingsHelper(s, 0, len);
}


