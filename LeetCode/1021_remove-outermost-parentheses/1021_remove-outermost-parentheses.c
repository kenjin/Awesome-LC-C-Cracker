
char * removeOuterParentheses(char * S)
{
	int len = strlen(S);
	int ctr = 0;
	int idx = 0;
	char *ret = calloc(len+1, sizeof(char));
	for (int i = 0; i < len; i++)
	{
		if (S[i] == '(')
		{
			ctr++;
		} else
		{            
			ctr--;
			// Get outer parentheses, remvoe it
			if (ctr == 0)
			{
				S[i] = '\0';
				strcat(ret, &(S[idx+1]));
				idx = i+1;
			}
		}
	}    
	return ret;
}

