
static inline void swap(int *x, int *y)
{
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

static void heapify(int *arr, int size, int cur)
{
    int left = (cur << 1) + 1, right = (cur << 1) + 2;
    int max = cur;

    if (left < size && arr[left] > arr[max])
        max = left;
    if (right < size && arr[right] > arr[max])
        max = right;

    if (max != cur) {
        swap(&arr[max], &arr[cur]);
        heapify(arr, size, max);
    }
}

static void create_heap(int *arr, int size)
{
    for (int i = ((size - 1) >> 1); i >= 0; i--)
        heapify(arr, size, i);
}

int lastStoneWeight(int *stones, int stones_sz)
{
    create_heap(stones, stones_sz);
    for (int i = 0; i < stones_sz; i++)
        printf("%d ", stones[i]);
    printf("\n");

    while (stones_sz >= 4) {
        /* get the idx of second largest element, that is, return 1 or 2 */
        int max2_idx = (stones_sz > 2 && stones[2] > stones[1]) ? 2 : 1;
        int diff = abs(stones[0] - stones[max2_idx]);
        /* handle two smash conditions */
        stones[0] = stones[stones_sz - 1];
        stones[max2_idx] = (diff == 0 ? stones[stones_sz - 2] : diff);
        stones_sz = (diff == 0 ? stones_sz - 2 : stones_sz - 1);
        /* adjust max heap */
        heapify(stones, stones_sz, max2_idx);
        heapify(stones, stones_sz, 0);
    }

    if (stones_sz == 3)
        return abs(stones[0] - stones[1] - stones[2]);
    else if (stones_sz == 2)
        return abs(stones[0] - stones[1]);
    else
        return (stones_sz == 1 ? stones[0] : 0);
}