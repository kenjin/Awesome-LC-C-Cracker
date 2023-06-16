
char * addStrings(char * num1, char * num2)
{
	// Scan the string from tail idx to head idx
	int idx1 = strlen(num1)-1;
	int idx2 = strlen(num2)-1;
	char *ret = calloc(5102, sizeof(char));
	int idxRet = 5100;
	int carry = 0;
	while (idx1 >= 0 || idx2 >= 0)
	{
		int sum = 0;
		if (idx1 >= 0)
		{
			sum += num1[idx1] - '0';
			idx1--;
		}
		if (idx2 >= 0)
		{
			sum += num2[idx2] - '0';
			idx2--;
		}
		sum += carry;
		ret[idxRet] = sum % 10 + '0';
		carry = sum / 10;
		idxRet--;
	}

	if (carry)
	{
		ret[idxRet] = '1';
		idxRet--;
	}

	return &(ret[idxRet+1]);
}

