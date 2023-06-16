
int compare(const void *a, const void *b)
{
	char *n1 = *(char **)a;
	char *n2 = *(char **)b;

	return strncmp(n1, n2, 5);
}

int getMinutes(char *s)
{
	return (((s[0]-'0')*10 + (s[1]-'0'))*60 + (s[3]-'0')*10 + (s[4]-'0'));
}

int findMinDifference(char ** timePoints, int timePointsSize)
{
	qsort(timePoints, timePointsSize, sizeof(char *), compare);    
	int min = 1441, tmp;
	for (int i = 1; i < timePointsSize; i++)
	{
		tmp = getMinutes(timePoints[i]) - getMinutes(timePoints[i-1]);        
		min = (tmp < min ? tmp : min);
	}

	tmp = getMinutes(timePoints[0]) - getMinutes(timePoints[timePointsSize-1]) + 1440;
	return (tmp < min ? tmp : min);;
}


