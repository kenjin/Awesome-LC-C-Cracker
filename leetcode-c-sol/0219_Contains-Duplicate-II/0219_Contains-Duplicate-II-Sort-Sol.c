typedef struct {
    int val;
    int idx;
} data_t;

static int cmp(const void* a, const void* b) { return (*(data_t *)a).val - (*(data_t *)b).val; }

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    data_t* d = malloc(sizeof(data_t) * numsSize);
    for (int i = 0; i < numsSize; i++) {
        d[i].val = nums[i];
        d[i].idx = i;
    }

    qsort(d, numsSize, sizeof(data_t), cmp);

    bool ret = false;
    for (int i = 1; i < numsSize; i++) {
        if (d[i].val == d[i - 1].val && d[i].idx - d[i - 1].idx <= k) {
            ret = true;
            break;
        }
    }

    free(d);
    return ret;
}
