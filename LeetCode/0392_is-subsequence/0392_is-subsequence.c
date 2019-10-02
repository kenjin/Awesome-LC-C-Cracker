
bool isSubsequence(char * s, char * t)
{
	while (*t)
	{
		if (*s == *t)
		{
			s++;
			t++;
		} else
		{
			t++;
		}
	}

	return (*s == 0 ? true : false);
}

