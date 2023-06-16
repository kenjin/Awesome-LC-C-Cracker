static int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void wiggleSort(int* nums, int numsSize)
{
    int *bak = malloc(sizeof(int)*numsSize);
    memcpy(bak, nums, sizeof(int)*numsSize);
    qsort(bak, numsSize, sizeof(int), cmp);

    int spart_idx = ((numsSize - 1) >> 1), lpart_idx = numsSize - 1;
    for (int i = 0; i < numsSize; i++) {
        if (i & 0x1) {
            nums[i] = bak[lpart_idx];
            lpart_idx--;
        } else {
            nums[i] = bak[spart_idx];
            spart_idx--;
        }
    }
    free(bak);
}

