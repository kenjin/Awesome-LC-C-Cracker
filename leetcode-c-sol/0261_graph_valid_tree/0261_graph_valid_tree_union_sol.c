static int set_find(int *set, int target)
{
    if (set[target] == -1)
        return target;

    int tmp = target;
    while (set[target] != -1)
        target = set[target];

    set[tmp] = target;
    return target;
}

static void set_union(int *set, int n1, int n2)
{
    // Consider the smaller one as the root
    if (n1 < n2)
        set[n2] = n1;
    else
        set[n1] = n2;
}

bool validTree(int n, int** edges, int edgesSize, int* edgesColSize)
{
    // a tree with n nodes has n -1 edges.
    if (edgesSize != n - 1)
        return false;

    int *set = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        set[i] = -1;

    for (int i = 0; i < edgesSize; i++) {
        if (set_find(set, edges[i][0]) == set_find(set, edges[i][1]))
            return false;
        set_union(set, edges[i][0], edges[i][1]);
    }

    free(set);
    return true;
}
