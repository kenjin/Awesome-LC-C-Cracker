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

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 * };
 */

int compare(struct Interval* a, struct Interval* b)
{
    if (a->start == b->start)
    {
        return (a->end - b->end);
    } else
    {
        return (a->start - b->start);
    }
}

int minMeetingRooms(struct Interval* intervals, int intervalsSize) {
    qsort(intervals, intervalsSize, sizeof(struct Interval), compare);

    struct Interval *roomSet = (struct Interval *)malloc(sizeof(struct Interval));
    int rCtr = 0;
    for (int curIdx = 0; curIdx < intervalsSize; curIdx++)
    {
        int combine = 0;
        for (int setIdx = 0; setIdx < rCtr; setIdx++)
        {
            /* Can combine to the same set */
            if (intervals[curIdx].start >= roomSet[setIdx].end)
            {
                combine = 1;
                /* Update ending time */
                roomSet[setIdx].end = intervals[curIdx].end;
                //printf("Update setIdx=%d, [%d-%d]\n", setIdx, roomSet[setIdx].start, roomSet[setIdx].end);
                break;
            }
        }

        if (!combine)
        {
            rCtr += 1;
            roomSet = realloc(roomSet, sizeof(struct Interval) * rCtr);
            roomSet[rCtr-1].start = intervals[curIdx].start;
            roomSet[rCtr-1].end = intervals[curIdx].end;
            //printf("Add rCtr=%d, [%d-%d]\n", rCtr-1, roomSet[rCtr-1].start, roomSet[rCtr-1].end);
        }
    }

    return rCtr;
}
