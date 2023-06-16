#define MAX_LEN     3001

bool isVowel(char c)
{
	return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
			c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

void goatLatinHandler(char *S, char *ret, int repeatA)
{
	if (isVowel(S[0]))  // Rule 1
	{
		strcat(ret, S);        
	} else              // Rule 2
	{
		strcat(ret, &S[1]);
		S[1] = 0;
		strcat(ret, &S[0]);                
	}
	strcat(ret, "ma");
	for (int x = 0; x < repeatA; x++) // Rule 3
	{
		strcat(ret, "a");
	}
}

char * toGoatLatin(char * S)
{
	char *ret = calloc(MAX_LEN, sizeof(char));
	char *delim = " ";
	char *pch;
	pch = strtok(S, delim);
	int idx = 1;
	while (pch != NULL)
	{
		goatLatinHandler(pch, ret, idx);
		strcat(ret, " ");
		pch = strtok(NULL, delim);
		idx++;
	}

	int retLen = strlen(ret);
	ret[retLen-1] = 0;

	return ret;
}


