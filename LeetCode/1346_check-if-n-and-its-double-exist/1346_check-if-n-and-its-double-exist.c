typedef struct {
    int used;
    int data;
} BUCKET;

#define MIN_VAL 1000*2

static inline int hash(int val, int size)
{
    return (val + MIN_VAL) % size;
}

static inline void hash_add(BUCKET *h, int size, int val)
{
    bool ret = false;
    int idx = hash(val, size);
    while (h[idx].used) {
        idx = (idx + 1) % size;
    }

    h[idx].used = 1;
    h[idx].data = val;
}

static inline bool hash_find(BUCKET *h, int size, int val)
{
    bool ret = false;
    int idx = hash(val, size);
    while (h[idx].used) {
        if (h[idx].data == val) {
            ret = true;
            break;
        }
        idx = (idx + 1) % size;
    }

    return ret;
}

/* Constraints: -10^3 <= arr[i] <= 10^3 */
bool checkIfExist(int *arr, int arrSize)
{
    BUCKET *h_set = calloc(arrSize + 1, sizeof(BUCKET));
    bool ret = false;
    for (int i = 0; i < arrSize; i++) {
        if (hash_find(h_set, arrSize + 1, ((unsigned int)arr[i] << 1))) {
            ret = true;
            break;
        }

        if ((arr[i] & 0x1) == 0x0 &&
            hash_find(h_set, arrSize + 1, (arr[i] >> 1))) {
            ret = true;
            break;
        }

        hash_add(h_set, arrSize + 1, arr[i]);
    }

    free(h_set);
    return ret;
}
