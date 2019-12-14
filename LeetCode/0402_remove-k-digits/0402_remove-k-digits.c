
char * removeKdigits(char * num, int k)
{
	int len = strlen(num);
	char *tmpNum = calloc(len+1, sizeof(char));
	strcpy(tmpNum, num);
	for (int i = 0; i < k; i++)
	{
		int pre = -1;
		for (int x = 0; x < len; x++)
		{
			if (tmpNum[x] == 'x')
			{
				continue;
			}

			if (pre == -1)
			{
				pre = x;
				continue;
			}

			if (tmpNum[x] < tmpNum[pre])
			{
				break;
			} else
			{
				pre = x;
			}
		}
		tmpNum[pre] = 'x';
	}

	int numCtr = 0;
	for (int x = 0; x < len; x++)
	{
		if (tmpNum[x] == 'x' || (numCtr == 0 && tmpNum[x] == '0'))
		{
			continue;
		}
		num[numCtr] = tmpNum[x];
		numCtr++;
	}
	num[numCtr] = 0;

	free(tmpNum);
	return (numCtr == 0 ? "0" : num); 
}


