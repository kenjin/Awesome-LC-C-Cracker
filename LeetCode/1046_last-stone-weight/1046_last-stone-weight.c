static inline void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapify(int *arr, int size, int idx)
{
    int left = (idx << 1) + 1;
    int right = (idx << 1) + 2;
    int max_idx = idx;

    if (right < size && arr[right] > arr[max_idx])
        max_idx = right;

    if (left < size && arr[left] > arr[max_idx])
        max_idx = left;

    if (max_idx != idx) {
        swap(&(arr[max_idx]), &(arr[idx]));
        heapify(arr, size, max_idx);
    }
}

static inline void create_heap(int *arr, int size)
{
    for (int i = ((size - 1) >> 1); i >= 0; i--)
        heapify(arr, size, i);
}

int lastStoneWeight(int *stones, int stonesSize)
{
    create_heap(stones, stonesSize);
    while (stonesSize >= 4) {
        int max2 = (stonesSize > 2 && stones[2] > stones[1]) ? 2 : 1;
        int diff = abs(stones[0] - stones[max2]);

        stones[0] = stones[stonesSize - 1];
        stones[max2] = (diff == 0 ? stones[stonesSize - 2] : diff);
        stonesSize = (diff == 0 ? stonesSize - 2 : stonesSize - 1);

        heapify(stones, stonesSize, max2);
        heapify(stones, stonesSize, 0);
    }

    if (stonesSize == 3)
        return abs(stones[0] - stones[1] - stones[2]);
    else if (stonesSize == 2)
        return abs(stones[0] - stones[1]);
    else
        return (stonesSize == 1 ? stones[0] : 0);
}
