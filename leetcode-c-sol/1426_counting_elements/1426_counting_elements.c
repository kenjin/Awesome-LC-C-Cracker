#define ARR_MAX_VAL 1000

int countElements(int *arr, int arrSize)
{
    char *ht = calloc(ARR_MAX_VAL + 1, sizeof(char));
    for (int i = 0; i < arrSize; i++) {
        ht[arr[i]] = 1;
    }

    int ret = 0;
    for (int i = 0; i < arrSize; i++) {
        if (arr[i] < ARR_MAX_VAL && ht[arr[i] + 1])
            ret++;
    }
    free(ht);

    return ret;
}
