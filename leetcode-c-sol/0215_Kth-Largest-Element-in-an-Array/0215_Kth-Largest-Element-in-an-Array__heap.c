static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapify(int *nums, int cur, int size)
{
    int l_chd = (cur << 1) + 1;
    int r_chd = (cur << 1) + 2;
    int max = cur;
    if (l_chd < size && nums[l_chd] > nums[max])
        max = l_chd;
    if (r_chd < size && nums[r_chd] > nums[max])
        max = r_chd;

    if (max != cur) {
        swap(&nums[max], &nums[cur]);
        heapify(nums, max, size);
    }
}

static int del_max_heap(int *nums, int size)
{
    int ret = nums[0];
    nums[0] = nums[size - 1];
    heapify(nums, 0, size);
    return ret;
}

static void create_heap(int *nums, int size)
{
    for (int i = (size - 1) / 2; i >= 0; i--)
        heapify(nums, i, size);
}

int findKthLargest(int *nums, int nums_sz, int k)
{
    create_heap(nums, nums_sz);
    int ret = 0;
    for (int i = 0; i < k; i++)
        ret = del_max_heap(nums, nums_sz--);

    return ret;
}
