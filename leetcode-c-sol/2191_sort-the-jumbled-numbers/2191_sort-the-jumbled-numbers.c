typedef struct
{
    int num;
    int mapped_num;
} nums_info_t;

static int cmp(const void *a, const void *b)
{
    nums_info_t *n1 = (nums_info_t *)a;
    nums_info_t *n2 = (nums_info_t *)b;
    return ( (*(nums_info_t *)a).mapped_num > (*(nums_info_t *)b).mapped_num ? 1 : -1);
}

int* sortJumbled(int* mapping, int mappingSize, int* nums, int numsSize, int* returnSize)
{
    nums_info_t *ninfo = malloc(sizeof(nums_info_t)*numsSize);
    for (int i = 0; i < numsSize; i++) {
        int cur = nums[i], res = 0, base = 1;
        while (cur > 0 || base == 1) {
            res += mapping[cur % 10] * base;
            cur /= 10;
            base *= 10;
        }
        ninfo[i].num = nums[i];
        ninfo[i].mapped_num = res;
    }

    qsort(ninfo, numsSize, sizeof(nums_info_t), cmp);

    for (int i = 0; i < numsSize; i++)
        nums[i] = ninfo[i].num;

    free(ninfo);
    *returnSize = numsSize;
    return nums;
}
