
bool rotateString(char * A, char * B)
{
	int lenA = strlen(A);
	int lenB = strlen(B);
	if (lenA != lenB)
	{
		return false;
	}
	if (lenA == 0)
	{
		return true;
	}

	int ctr = 0;
	while (ctr < lenA-1)
	{
		char tmp = A[0];
		for (int i = 0; i < lenA-1; i++)
		{
			A[i] = A[i+1];
		}

		A[lenA-1] = tmp;

		if (strcmp(A, B) == 0)
		{
			return true;
		}

		ctr++;
	}
	return false;     
}

