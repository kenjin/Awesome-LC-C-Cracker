typedef struct
{
    int val;
    int idx;
} data_t;

typedef struct
{
    int sz;
    data_t *d;
} hash_t;

static inline int do_hash(hash_t *h, int key) 
{
    int r = key % h->sz;
    return r < 0 ? r + h->sz : r;
}

static void add_hash(hash_t *h, int target, int t_idx)
{
    int idx = do_hash(h, target);
    while (h->d[idx].idx)
        idx = (idx + 1) % h->sz;

    h->d[idx].val = target;
    h->d[idx].idx = t_idx + 1;
}

static int find_hash(hash_t *h, int target)
{
    int idx = do_hash(h, target);
    while (h->d[idx].idx) {
        if (h->d[idx].val == target)
            return h->d[idx].idx - 1;
        idx = (idx + 1) % h->sz;
    }
    return -1;
}

static hash_t* create_hash(int sz)
{
    hash_t *obj = malloc(sizeof(hash_t));
    obj->sz = sz;
    obj->d = calloc(sz, sizeof(data_t));
    return obj;
}

static inline void release_hash(hash_t *h)
{
    free(h->d);
    free(h);
}

bool checkSubarraySum(int* nums, int numsSize, int k)
{
    int rem = 0;
    bool ret = false;
    hash_t *h = create_hash(numsSize << 1);

    for (int i = 0; i < numsSize; i++) {
        rem = (rem + nums[i]) % k;
        // Subarray len >= 2 and prefix sum could be divided by k
        if (i > 0 && rem == 0) {
            ret = true;
            break;
        }
        int idx = find_hash(h, rem);
        if (idx != -1 && (i - idx) > 1){
            ret = true;
            break;
        }
        add_hash(h, rem, i);
        printf("%d: Add rem %d \n", i, rem);
    }

    release_hash(h);
    return ret;
}
