
char* transfer(char *S)
{
	int maxLen = strlen(S);
	char *s = S;
	int idx = 0;
	while(*s)
	{
		if (*s == '#')
		{
			S[idx] = '\0';
			if (idx > 0)
			{
				idx--;
				S[idx] = '\0';
			}
		} else
		{
			S[idx] = *s;
			idx++;
		}
		s++;
	}

	if (idx < maxLen)
	{
		S[idx] = 0;
	}
	return S;
}

bool backspaceCompare(char * S, char * T)
{
	S = transfer(S);
	T = transfer(T);
	return (0 == strcmp(S, T) ? true : false);
}


