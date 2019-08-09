/**
 * *********************************************************************
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * int guess(Master *, char *word);
 */

bool match(char *a, char *b, int match)
{
	int ret = 0;
	for (int i = 0; i < 6; i++)
	{
		ret = (a[i] == b[i] ? ret + 1 : ret);
	}

	return (ret == match ? true : false);
}

void findSecretWord(char** wordlist, int wordlistSize, Master* master) 
{
	srand(time(NULL));
	int *set = malloc(sizeof(int)*wordlistSize);
	for (int i = 0; i < wordlistSize; i++)
	{
		set[i] = i;
	}
	int *tmp = malloc(sizeof(int)*wordlistSize);
	int setCtr = wordlistSize;

	int first = 0;
	// Update set
	for (int i = 0; i < 10; i++)
	{
		int ranNum = rand();
		int guessIdx = set[ranNum % setCtr];
		int ret = guess(master, wordlist[guessIdx]);
		if (ret == 6)
		{
			break;
		}

		int tmpCtr = 0;
		for (int x = 0; x < setCtr; x++)
		{
			int idx = set[x];
			if (idx == guessIdx)
			{
				continue;
			}

			if (match(wordlist[idx], wordlist[guessIdx], ret))
			{
				tmp[tmpCtr] = idx;
				tmpCtr++;                
			}
		}

		memcpy(set, tmp, sizeof(int)*tmpCtr);
		setCtr = tmpCtr;
	}

	free(set);
	free(tmp);
}

