
char * getHint(char * secret, char * guess)
{
	int setSecret[10] = {0}, setGuess[10] = {0};
	int len = strlen(secret);

	int bulls = 0, cows = 0;
	for (int i = 0; i < len; i++)
	{
		setSecret[secret[i]-'0'] ++;
		setGuess[guess[i]-'0'] ++;
		if (secret[i] == guess[i])
		{
			bulls++;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		cows += (setSecret[i] < setGuess[i] ? setSecret[i] : setGuess[i]);
	}

	char *ret = calloc(len+4, sizeof(char));
	sprintf(ret, "%dA%dB", bulls, cows-bulls);

	return ret;
}

