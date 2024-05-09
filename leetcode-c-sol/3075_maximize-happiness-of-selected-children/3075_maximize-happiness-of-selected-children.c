static int cmp(const void *a, const void *b) { return *(int *)b - *(int *)a; }

long long maximumHappinessSum(int* happiness, int happinessSize, int k)
{
    qsort(happiness, happinessSize, sizeof(int), cmp);
    long long ret = 0;
    for (int i = 0; i < k; i++) {
        if (happiness[i] - i <= 0)
            break;
        ret += happiness[i] - i;
    }

    return ret;
}
