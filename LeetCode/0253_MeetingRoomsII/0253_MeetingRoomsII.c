/**
Given an array of meeting time intervals consisting of start and end 
times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of 
conference rooms required.

Example 1:

Input: [[0, 30],[5, 10],[15, 20]]
Output: 2
Example 2:

Input: [[7,10],[2,4]]
Output: 1

*/

typedef struct roomInfo
{
	int start;
	int end;
}ROOM;

int compare(const void *a, const void *b)
{
	int *n1 = *(int **)a;
	int *n2 = *(int **)b;

	return (n1[0] - n2[0]);
}

int minMeetingRooms(int** intervals, int intervalsSize, int* intervalsColSize)
{
	qsort(intervals, intervalsSize, sizeof(int *), compare);
	int roomSize = 0;
	ROOM *r = malloc(sizeof(ROOM));
	for (int i = 0; i < intervalsSize; i++)
	{
		int found = 0;
		for (int x = 0; x < roomSize; x++)
		{
			if (intervals[i][0] >= r[x].end) /* Update room info */
			{
				r[x].end = intervals[i][1];
				found = 1;
				break;
			}
		}
		if (!found)
		{
			roomSize++;
			r = realloc(r, sizeof(ROOM)*roomSize);
			r[roomSize-1].start = intervals[i][0];
			r[roomSize-1].end = intervals[i][1];
		}
	}

	free(r);
	return roomSize;
}
