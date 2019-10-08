
char* checkDivisor(char *S, char *T)
{
	int lenS = strlen(S);
	int lenT = strlen(T);
	while (lenS > 0)
	{
		char *tmp = strstr(S, T);
		if (tmp != NULL)
		{
			lenS -= lenT;
			if (lenS == 0)
			{
				return T;
			}
		} else
		{
			break;
		}
		S += lenT;
	}

	return "";
}

char * gcdOfStringsHelper(char * str1, char * str2, int len1, int len2)
{
	char *str2_cpy = calloc(len2+1, sizeof(char));
	strcpy(str2_cpy, str2);
	for (int i = len2; i > 0; i--)
	{
		if (len2 % i != 0)
		{
			continue;
		}
		char tmpChar = str2_cpy[i];
		str2_cpy[i] = 0;

		char *ret = checkDivisor(str2, str2_cpy);
		if (strlen(ret) != 0)
		{
			ret = checkDivisor(str1, str2_cpy);
			if (strlen(ret) != 0)
			{
				return ret;
			}
		}
		str2_cpy[i] = tmpChar;
	}

	free(str2_cpy);
	return "";
}

char * gcdOfStrings(char * str1, char * str2)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	if (len1 > len2)
	{
		return gcdOfStringsHelper(str1, str2, len1, len2);   
	} else
	{
		return gcdOfStringsHelper(str2, str1, len2, len1);
	}
}

