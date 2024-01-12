/*
 * You have a graph of n nodes. You are given an integer n and an array edges where edges[i] = [ai, bi] indicates that there is an edge between ai and bi in the graph.
 * Return the number of connected components in the graph.
 */

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

int countComponents(int n, int** edges, int edgesSize, int* edgesColSize)
{
    int *set = malloc(sizeof(int)*n);
    char *chk = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        set[i] = i;

    for (int i = 0; i < edgesSize; i++)
        set_union(set, edges[i][0], edges[i][1]);

    int ret = 0;
    for (int i = 0; i < n; i++) {
        if (chk[set_find(set, i)] == 0) {
            chk[set[i]] = 1;
            ret++;
        }
    }

    free(set);    
    free(chk);
    return ret;
}
