
char * boldWords(char ** words, int wordsSize, char * S)
{
	int sLen = strlen(S);
	char *validS = calloc(sLen+1, sizeof(char));
	for (int i = 0; i < wordsSize; i++)
	{
		char *tmpS = S;
		char *res = strstr(S, words[i]);
		int cmpLen = strlen(words[i]);
		while (res)
		{           
			int startIdx = res - tmpS;
			for (int x = 0; x < cmpLen; x++)
			{
				validS[startIdx+x] = 1;
			}

			res++;            
			res = strstr(res, words[i]);
		}
	}

	char *ret = calloc(sLen*8, sizeof(char));
	int retCtr = 0;
	char inBold = 0;
	for (int i = 0; i < sLen; i++)
	{
		if (validS[i])
		{
			if (!inBold)
			{
				strcat(ret, "<b>");
				retCtr += 3;                
			}           
			inBold = 1;
		} else
		{
			if (inBold)
			{
				strcat(ret, "</b>");
				retCtr += 4;                
			}           
			inBold = 0;
		}        
		ret[retCtr] = S[i];
		retCtr++; 
	}

	if (inBold)
	{
		strcat(ret, "</b>");
		retCtr += 4;                
	}

	return ret;
}

