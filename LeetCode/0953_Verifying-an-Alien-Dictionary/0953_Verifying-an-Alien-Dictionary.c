
bool isAlienSorted(char ** words, int wordsSize, char * order)
{
	char alien[27];
	alien[0] = 0; // reserve index zero for '\0'
	for (int i = 0; i < 26; i++)
	{
		int idx = order[i] - 'a' + 1;
		alien[idx] = i;
	}

	char *prev = words[0];
	for (int i = 1; i < wordsSize; i++)
	{        
		int cur = 0;
		while (1)
		{
			char n1 = (prev[cur] == 0 ? 0 : prev[cur] - 'a' + 1);
			char n2 = (words[i][cur] == 0 ? 0 : words[i][cur] - 'a' + 1);
			if (alien[n1] < alien[n2])
			{
				break; 
			} else if  (alien[n1] > alien[n2])
			{
				return false;
			}            
			cur++;
		}
		prev = words[i];
	}

	return true;
}

