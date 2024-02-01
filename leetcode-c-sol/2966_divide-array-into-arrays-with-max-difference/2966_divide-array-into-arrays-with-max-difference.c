static void heapify(int* nums, int cur, int size) {
    int min = cur;
    int l = (cur << 1) + 1;
    int r = (cur << 1) + 2;
    if (l < size && nums[l] < nums[min])
        min = l;
    if (r < size && nums[r] < nums[min])
        min = r;

    if (min != cur) {
        int tmp = nums[min];
        nums[min] = nums[cur];
        nums[cur] = tmp;
        heapify(nums, min, size);
    }
}

static void create_heap(int* nums, int size) {
    for (int i = ((size - 1) >> 1); i >= 0; i--)
        heapify(nums, i, size);
}

int** divideArray(int* nums, int numsSize, int k, int* returnSize,
                  int** returnColumnSizes) {
    if (numsSize % 3) {
        *returnSize = 0;
        return NULL;
    }

    create_heap(nums, numsSize);

    int** ret = malloc(sizeof(int*) * (numsSize / 3));
    *returnColumnSizes = malloc(sizeof(int*) * (numsSize / 3));
    *returnSize = 0;
    while (numsSize > 0) {
        int n[3] = {0};
        for (int x = 0; x < 3; x++) {
            n[x] = nums[0];
            nums[0] = nums[numsSize - 1];
            numsSize--;
            heapify(nums, 0, numsSize);
        }
        if (abs(n[0] - n[1]) > k || abs(n[1] - n[2]) > k ||
            abs(n[0] - n[2]) > k) {
            *returnSize = 0;
            return NULL;
        }
        ret[*returnSize] = malloc(sizeof(int) * 3);
        (*returnColumnSizes)[*returnSize] = 3;
        ret[*returnSize][0] = n[0];
        ret[*returnSize][1] = n[1];
        ret[*returnSize][2] = n[2];
        *returnSize += 1;
    }

    return ret;
}
