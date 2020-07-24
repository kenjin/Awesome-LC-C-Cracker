static int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

int heightChecker(int *heights, int heights_sz)
{
    int *cpy = malloc(sizeof(int) * heights_sz);
    memcpy(cpy, heights, sizeof(int) * heights_sz);
    qsort(cpy, heights_sz, sizeof(int), compare);

    int ret = 0;
    for (int i = 0; i < heights_sz; i++) {
        if (cpy[i] != heights[i])
            ret++;
    }

    free(cpy);
    return ret;
}