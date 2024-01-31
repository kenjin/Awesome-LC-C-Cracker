static int set_find(int *set, int target)
{
    if (set[target] == target)
        return target;

    int ret = set_find(set, set[target]);
    set[target] = ret;
    return ret;
}

static void set_union(int *set, int x, int y)
{
    x = set_find(set, x);
    set[x] = set_find(set, y);
}

bool validPath(int n, int** edges, int edgesSize, int* edgesColSize, int source, int destination)
{
    int *set = malloc(sizeof(int)*n+1);
    for (int i = 0; i < n; i++)
        set[i] = i;

    for (int i = 0; i < edgesSize; i++)
        set_union(set, edges[i][0], edges[i][1]);

    bool ret = (set_find(set, source) == set_find(set, destination)) ;
    free(set);
    return ret;
}

