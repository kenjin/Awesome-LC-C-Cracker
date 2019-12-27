
#define M_MASK    (0x3F)
#define H_MASK    (0x3C0)

void readBinaryWatchHelp(int num, int curIdx, char **ret, int *retSize, int time)
{
	if (curIdx > 10)
	{
		return;
	}
	if (num == 0)
	{
		int hour = (time & H_MASK) >> 6;
		int min = (time & M_MASK);        
		if (hour < 12 && hour >= 0 && min < 60 && min >= 0)
		{
			ret[*retSize] = calloc(6, sizeof(char));  
			sprintf(ret[*retSize], "%d:%02d", hour, min);           
			*retSize += 1;
		}
		return;
	}

	time |= (0x1 << curIdx);    
	readBinaryWatchHelp(num-1, curIdx+1, ret, retSize, time);    
	time &= ~(0x1 << curIdx);
	readBinaryWatchHelp(num, curIdx+1, ret, retSize, time);    
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** readBinaryWatch(int num, int* returnSize)
{
	int time = 0, total = 1, cur = 10, div = 1;
	for (int i = 1; i <= num; i++)
	{
		total *= cur;
		cur--;
		div *= i;
	}
	total /= div;

	char **ret = malloc(sizeof(char *)*total);
	*returnSize = 0;
	readBinaryWatchHelp(num, 0, ret, returnSize, time);
	return ret;
}


