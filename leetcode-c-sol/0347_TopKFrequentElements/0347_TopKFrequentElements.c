/**

347. Top K Frequent Elements Medium

Given a non-empty array of integers, return the k most frequent elements.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
Note:

You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the
array's size.

 */

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

static int compare(const void *a, const void *b)
{
    return (*(DATA *) b).dup - (*(DATA *) a).dup;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *topKFrequent(int *nums, int nums_sz, int k, int *ret_sz)
{
    HASH *h = hash_create(nums_sz + 1);

    for (int i = 0; i < nums_sz; i++) {
        if (!hash_update(h, nums[i])) {
            hash_add(h, nums[i]);
        }
    }

    qsort(h->arr, nums_sz + 1, sizeof(DATA), compare);

    *ret_sz = k;
    int *ret = malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++) {
        ret[i] = h->arr[i].val;
    }

    hash_release(h);
    return ret;
}
