/***

Approach: Union Set/Find

- Sort the meetings by time.
- Use a "known" arr to record whether a person knows the secret, and use a set
  to maintain the "known secret" relationship.
- Perform union-find operations on meetings happening at the same time, then
  check the union set and "known" array.
    => Add the person as "known" if one of the union set partners knows the
       secret.
    => For the person who does NOT know the secret at this time, unmerge this
       person.

***/

static int set_find(int* set, int target) {
    if (set[target] == target)
        return target;

    int ret = set_find(set, set[target]);
    set[target] = ret;
    return ret;
}

static void set_union(int* set, int x, int y) {
    x = set_find(set, x);
    set[x] = set_find(set, y);
}

static void set_unmerge(int* set, int target) { set[target] = target; }

static int compare(const void* a, const void* b) {
    return (*(int**)a)[2] - (*(int**)b)[2];
}

int* findAllPeople(int n, int** meetings, int meetingsSize,
                   int* meetingsColSize, int firstPerson, int* returnSize) {
    qsort(meetings, meetingsSize, sizeof(int*), compare);
    int* ret = malloc(sizeof(int) * n);
    *returnSize = 0;

    int set[n], known[n];
    for (int i = 0; i < n; i++) {
        set[i] = i;
        known[i] = 0;
    }

    // Init person 0 and 1st persion
    known[0] = 1;
    known[firstPerson] = 1;
    set_union(set, firstPerson, 0);

    int prev_t_idx = 0, cur_idx = 0;
    while (cur_idx < meetingsSize) {
        while (cur_idx < meetingsSize &&
               meetings[prev_t_idx][2] == meetings[cur_idx][2]) {
            int p1 = set_find(set, meetings[cur_idx][0]);
            int p2 = set_find(set, meetings[cur_idx][1]);
            if (known[p1])
                set_union(set, meetings[cur_idx][1], meetings[cur_idx][0]);
            else
                set_union(set, meetings[cur_idx][0], meetings[cur_idx][1]);

            cur_idx++;
        }

        for (int x = prev_t_idx; x < cur_idx; x++) {
            int p1 = set_find(set, meetings[x][0]);
            int p2 = set_find(set, meetings[x][1]);
            if (known[p1] || known[p2]) {
                known[meetings[x][0]] = known[meetings[x][1]] = 1;
            } else {
                set_unmerge(set, meetings[x][0]);
                set_unmerge(set, meetings[x][1]);
            }
        }
        prev_t_idx = cur_idx;
    }

    for (int x = 0; x < n; x++) {
        if (known[x]) {
            ret[*returnSize] = x;
            *returnSize += 1;
        }
    }

    return ret;
}
