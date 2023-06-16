char* addCharToString(char *s, char c, int size)
{
	s = realloc(s, sizeof(char)*size + 1);
	s[size-1] = c;
	s[size] = 0;

	return s;
}

char* decode(char *s, int *head, int *res)
{
	int len = strlen(s);
	int resLen = strlen(res);
	while (*head < len && s[*head] != ']')
	{
		if (('a' <= s[*head] && s[*head] <= 'z') ||
				('A' <= s[*head] && s[*head] <= 'Z'))
		{
			resLen++;
			res = addCharToString(res, s[*head], resLen);
			*head += 1;
		} else
		{
			int repeat = 0;
			while ('0' <= s[*head] && s[*head] <= '9')
			{
				repeat = repeat*10 + (s[*head]-'0');
				*head += 1;
			}

			*head+=1; // skip '['     
			char *tmpStr = calloc(1, sizeof(char));
			tmpStr = decode(s, head, tmpStr);
			*head+=1; // skip ']'

			int tmpLen = strlen(tmpStr);
			res = realloc(res, sizeof(char)*(resLen+tmpLen*repeat) + 1);
			for (int x = 0; x < repeat; x++)
			{
				strcat(res, tmpStr);
			}
			resLen += tmpLen*repeat;
			free(tmpStr);
		}
	}
	return res;
}

char * decodeString(char * s)
{
	char *res = calloc(1, sizeof(char));
	int idx = 0;
	res = decode(s, &idx, res);

	return res;
}


