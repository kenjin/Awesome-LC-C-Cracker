typedef struct {
    int *arr;
    int size;
} HEAP;

static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static inline bool heap_is_empty(HEAP *obj)
{
    return (obj->size == 0);
}

void heapify(HEAP *obj, int cur_idx)
{
    int max_idx = cur_idx;
    int l_idx = (cur_idx << 1) + 1;
    int r_idx = (cur_idx << 1) + 2;

    if (l_idx < obj->size && obj->arr[max_idx] < obj->arr[l_idx])
        max_idx = l_idx;
    if (r_idx < obj->size && obj->arr[max_idx] < obj->arr[r_idx])
        max_idx = r_idx;
    /* The max is left child or right child */
    if (max_idx != cur_idx) {
        swap(&(obj->arr[max_idx]), &(obj->arr[cur_idx]));
        heapify(obj, max_idx);
    }
}

int heap_del(HEAP *obj)
{
    int ret = obj->arr[0];
    obj->arr[0] = obj->arr[obj->size - 1];
    obj->size -= 1;
    heapify(obj, 0);

    return ret;
}

static inline HEAP *heap_create(int *n, int size)
{
    HEAP *obj = malloc(sizeof(HEAP));
    obj->arr = n;
    obj->size = size;

    for (int i = (size - 1) / 2; i >= 0; i--)
        heapify(obj, i);
    return obj;
}

static inline void heap_release(HEAP *obj)
{
    free(obj);
}

int thirdMax(int *nums, int numsSize)
{
    HEAP *h = heap_create(nums, numsSize);
    int ret, pre, tmp, del_num = 1;
    ret = heap_del(h);
    pre = ret;
    while (!heap_is_empty(h)) {
        tmp = heap_del(h);
        del_num = (tmp == pre ? del_num : del_num + 1);
        pre = tmp;
        if (del_num == 3) {
            ret = tmp;
            break;
        }
    }

    heap_release(h);
    return ret;
}
