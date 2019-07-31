
char * convert(char * s, int numRows)
{
	if (numRows == 1)
	{
		return s;
	}

	int base = numRows+(numRows-2);
	int len = strlen(s);
	char *ret = calloc(len+1, sizeof(char));
	int ctr = 0;
	int x, y;
	for (int i = 0; i < numRows; i++)
	{
		x = i;
		y = base-i;
		while (x < len)
		{
			ret[ctr] = s[x];
			x += base;
			ctr++;
			if (i > 0 && i < numRows-1 && y < len)
			{
				ret[ctr] = s[y];
				y += base;
				ctr++;
			}
		}
	}

	return ret;
}

