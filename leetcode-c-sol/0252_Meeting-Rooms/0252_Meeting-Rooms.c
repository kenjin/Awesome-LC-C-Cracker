
int compare(const void *a, const void *b)
{
	int *n1 = *(int **)a;
	int *n2 = *(int **)b;

	return n1[0] - n2[0];
}

bool canAttendMeetings(int** intervals, int intervalsSize, int* intervalsColSize)
{
	qsort(intervals, intervalsSize, sizeof(int*), compare);

	for (int i = 1; i < intervalsSize; i++)
	{
		if (intervals[i-1][1] > intervals[i][0])
		{
			return false;
		}
	}
	return true;
}

