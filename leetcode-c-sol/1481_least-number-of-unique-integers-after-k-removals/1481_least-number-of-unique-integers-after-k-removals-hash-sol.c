/*
 * 1. Use a hash table to store the frequency of each number.
 * 2. Sort the data by frequency, then remove k times from the smallest 
 *    frequency to the largest.
 * 3. Note that skip 0 freq when doing qsort compare fun.
 */

typedef struct {
    int val;
    int ctr;
} data_t;

typedef struct {
    int size;
    data_t* d;
} hash_t;

static hash_t* hash_init(int size) {
    hash_t* obj = malloc(sizeof(hash_t));
    obj->size = size;
    obj->d = calloc(size, sizeof(data_t));
    return obj;
}

static void hash_dinit(hash_t* h) {
    free(h->d);
    free(h);
}

static inline int do_hash(hash_t* h, int val) {
    int ret = val % (h->size);
    return (ret < 0 ? ret + h->size : ret);
}

static int hash_find_and_update(hash_t* h, int val) {
    int h_idx = do_hash(h, val);
    while (h->d[h_idx].ctr) {
        if (h->d[h_idx].val == val) {
            h->d[h_idx].ctr += 1;
            return h->d[h_idx].ctr;
        }
        h_idx = (h_idx + 1) % h->size;
    }
    return 0;
}

static void hash_add(hash_t* h, int val) {
    int h_idx = do_hash(h, val);
    while (h->d[h_idx].ctr) {
        h_idx = (h_idx + 1) % h->size;
    }
    h->d[h_idx].val = val;
    h->d[h_idx].ctr = 1;
}

static int compare(const void* a, const void* b) {
    data_t* n1 = (data_t*)a;
    data_t* n2 = (data_t*)b;

    if (n1->ctr == 0)
        return 1;
    if (n2->ctr == 0)
        return -1;

    return n1->ctr - n2->ctr;
}

int findLeastNumOfUniqueInts(int* arr, int arrSize, int k) {
    hash_t* h = hash_init(arrSize);
    int ret = 0;
    for (int i = 0; i < arrSize; i++) {
        if (!hash_find_and_update(h, arr[i])) {
            hash_add(h, arr[i]);
            // Update total numbers of unique value
            ret++;
        }
    }

    data_t* ptr = h->d;
    // sort by frequency
    qsort(ptr, arrSize, sizeof(data_t), compare);

    for (int idx = 0; k > 0; k--) {
        ptr[idx].ctr -= 1;
        if (ptr[idx].ctr == 0) {
            ret--; // Must remove the num when counts to zero
            idx++;
        }
    }

    hash_dinit(h);
    return ret;
}
