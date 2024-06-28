
static int cmp(const void *a, const void *b)
{
    return *(int *)b - *(int *)a;
}

long long maximumImportance(int n, int** roads, int roadsSize, int* roadsColSize)
{
    int *in_degree = calloc(n, sizeof(int));
    for (int i = 0; i < roadsSize; i++) {
        in_degree[roads[i][0]] += 1;
        in_degree[roads[i][1]] += 1;
    }

    qsort(in_degree, n, sizeof(int), cmp);
    long long ret = 0;
    for (int i = 0; i < n; i++)
        ret += (long long)in_degree[i] * (n - i);

    free(in_degree);
    return ret;
}
