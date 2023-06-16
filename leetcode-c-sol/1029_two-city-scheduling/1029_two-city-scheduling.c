static int compare(void *a, void *b)
{
    int *n1 = *(int **) a;
    int *n2 = *(int **) b;
    return (n1[0] - n1[1]) - (n2[0] - n2[1]);
}

int twoCitySchedCost(int **costs, int costsSize, int *costsColSize)
{
    qsort(costs, costsSize, sizeof(int *), compare);

    int ret = 0;
    for (int i = 0; i < costsSize / 2; i++)
        ret += costs[i][0] + costs[i + costsSize / 2][1];

    return ret;
}
