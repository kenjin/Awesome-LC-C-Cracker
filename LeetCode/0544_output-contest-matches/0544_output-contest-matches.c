typedef struct
{
	int len;
	char *s;
} MATCH;


char * findContestMatch(int n)
{
	MATCH *ret = malloc(sizeof(MATCH)*n);
	for (int i = 0; i < n; i++)
	{
		ret[i].s = calloc(2049, sizeof(char));
		ret[i].len = sprintf(ret[i].s, "%d", i+1);
	}

	while (n > 1)
	{
		for (int x = 0; x < n/2; x++)
		{
			char *tmp = calloc(ret[x].len + ret[n-x-1].len+4, sizeof(char));
			ret[x].len = sprintf(tmp, "(%s,%s)", ret[x].s, ret[n-x-1].s);            
			// release memory
			free(ret[x].s);
			free(ret[n-x-1].s);
			// point to new pointer
			ret[x].s = tmp;                        
		}
		n /= 2;
	}        

	char *result = calloc(ret[0].len+1, sizeof(char));
	strcpy(result, ret[0].s);
	free(ret);
	return result;
}

