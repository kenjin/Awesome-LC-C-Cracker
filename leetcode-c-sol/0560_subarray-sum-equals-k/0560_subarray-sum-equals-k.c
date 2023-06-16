
typedef struct __hash_data {
    int ctr;
    int val;
} DATA;

typedef struct __hash_table {
    int size;
    DATA *ptr;
} HASH;

static inline int hash(HASH *obj, int key)
{
    int r = key % obj->size;
    return r < 0 ? r + obj->size : r;
}

static HASH *create_hash(int size)
{
    HASH *obj = malloc(sizeof(HASH));
    obj->size = size;
    obj->ptr = calloc(size, sizeof(DATA));
    return obj;
}

static inline void release_hash(HASH *ht)
{
    free(ht->ptr);
    free(ht);
}

static void add_hash(HASH *ht, int key)
{
    int index = hash(ht, key);
    while (ht->ptr[index].ctr) {
        if (ht->ptr[index].val == key) {
            ht->ptr[index].ctr += 1;
            return;
        }
        index++;
        index %= ht->size;
    }
    ht->ptr[index].ctr = 1;
    ht->ptr[index].val = key;
}

static int find_hash(HASH *ht, int target)
{
    int index = hash(ht, target);
    while (ht->ptr[index].ctr) {
        if (ht->ptr[index].val == target)
            return ht->ptr[index].ctr;
        index++;
        index %= ht->size;
    }
    return 0;
}

int subarraySum(int *nums, int nums_sz, int k)
{
    HASH *h = create_hash(nums_sz * 2);
    int prefix_sum = 0, ret = 0;
    /* Consider the condition that prefix sum is match to k, add 0 to hash
     * table. That is, "prefix_sum + 0 = k" */
    add_hash(h, 0);
    for (int i = 0; i < nums_sz; i++) {
        prefix_sum += nums[i];
        ret += find_hash(h, prefix_sum - k);
        add_hash(h, prefix_sum);
    }
    release_hash(h);
    return ret;
}