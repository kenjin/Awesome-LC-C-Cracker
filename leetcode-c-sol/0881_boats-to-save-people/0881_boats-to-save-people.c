static int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int numRescueBoats(int* people, int peopleSize, int limit)
{
    qsort(people, peopleSize, sizeof(int), cmp);
    int head = 0, tail = peopleSize - 1, ret = 0;
    while (head <= tail) {
        if (people[tail] + people[head] <= limit)
            head++;

        tail--;
        ret++;
    }

    return ret;
}
