bool canIWinHelper(int maxChoosableInteger, int desiredTotal, char *used, int curChoose, int lv)
{    
	if (used[curChoose] != 0)
	{
		return (used[curChoose] == 1);
	}

	for (int i = 1; i <= maxChoosableInteger; i++)
	{
		int cur = (1 << i);
		if (curChoose & cur)
		{
			continue;
		}

		if (desiredTotal <= i || !canIWinHelper(maxChoosableInteger, desiredTotal-i, used, (curChoose|cur), lv+1))
		{
			used[curChoose] = 1;
			return true;
		}        
	}

	used[curChoose] = -1;
	return false;
}

bool canIWin(int maxChoosableInteger, int desiredTotal)
{    
	if (desiredTotal <= maxChoosableInteger)
	{
		return true;
	}
	if (maxChoosableInteger * (maxChoosableInteger + 1) / 2 < desiredTotal) 
	{
		return false;
	}

	int used[1048577] = {0};
	bool ret =  canIWinHelper(maxChoosableInteger, desiredTotal, used, 0, 0);

	return ret;
}
