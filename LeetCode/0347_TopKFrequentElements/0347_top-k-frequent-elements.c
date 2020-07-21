typedef struct {
    int used;
    int val;
    int dup;
} DATA;

typedef struct __hash_table {
    int size;
    DATA *arr;
} HASH;

static inline int hash(HASH *obj, int key)
{
    int r = key % obj->size;
    return r < 0 ? r + obj->size : r;
}

static inline HASH *hash_create(int size)
{
    HASH *obj = malloc(sizeof(HASH));
    obj->size = size;
    obj->arr = calloc(size, sizeof(DATA));
    return obj;
}

static inline void hash_add(HASH *ht, int val)
{
    int index = hash(ht, val);
    while (ht->arr[index].used) {
        index++;
        index %= ht->size;
    }
    ht->arr[index].used = 1;
    ht->arr[index].val = val;
    ht->arr[index].dup = 1;
}

static inline bool hash_update(HASH *ht, int target)
{
    int index = hash(ht, target);
    while (ht->arr[index].used) {
        if (ht->arr[index].val == target) {
            ht->arr[index].dup += 1;
            return true;
        }
        index++;
        index %= ht->size;
    }
    return false;
}

static inline void hash_release(HASH *ht)
{
    free(ht->arr);
    free(ht);
}

static void swap(DATA *a, DATA *b)
{
    DATA tmp = *a;
    *a = *b;
    *b = tmp;
}

static int partition(DATA *ptr, int head, int tail)
{
    int base_idx = head;
    for (int i = head; i < tail; i++) {
        if (ptr[i].dup > ptr[tail].dup)
            swap(&ptr[i], &ptr[base_idx++]);
    }
    swap(&ptr[tail], &ptr[base_idx]);
    return base_idx;
}

static void kth_smallest_qsort(DATA *ptr, int head, int tail, int k)
{
    if (head > tail)
        return;

    int pivot = partition(ptr, head, tail);
    if (pivot + 1 < k)
        kth_smallest_qsort(ptr, pivot + 1, tail, k);
    else if (pivot + 1 > k)
        kth_smallest_qsort(ptr, head, pivot - 1, k);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *topKFrequent(int *nums, int nums_sz, int k, int *ret_sz)
{
    HASH *h = hash_create(nums_sz + 1);

    for (int i = 0; i < nums_sz; i++) {
        if (!hash_update(h, nums[i]))
            hash_add(h, nums[i]);
    }

    kth_smallest_qsort(h->arr, 0, nums_sz, k);

    *ret_sz = k;
    int *ret = malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++)
        ret[i] = h->arr[i].val;

    hash_release(h);
    return ret;
}
