typedef struct {
    int val;
    int freq;
} data_t;

typedef struct {
    data_t* set;
    int size;
} hash_t;

static void dinit_hash(hash_t* h) {
    free(h->set);
    free(h);
}
static hash_t* init_hash(int sz) {
    hash_t* h = malloc(sizeof(hash_t));
    h->set = calloc(sz, sizeof(data_t));
    h->size = sz;
    return h;
}

static int find_hash(hash_t* h, int target) {
    int idx = target % h->size;
    while (h->set[idx].freq) {
        if (h->set[idx].val == target)
            return h->set[idx].freq;
        idx = (idx + 1) % h->size;
    }
    return 0;
}

static void update_hash(hash_t* h, int target, bool minus) {
    int idx = target % h->size;
    while (h->set[idx].freq) {
        if (h->set[idx].val == target) {
            h->set[idx].freq += (minus ? -1 : 1);
            return;
        }
        idx = (idx + 1) % h->size;
    }
    h->set[idx].val = target;
    h->set[idx].freq = 1;
}

int maxSubarrayLength(int* nums, int numsSize, int k) {
    hash_t* h = init_hash(100001);
    int ret = 0, head = 0;
    for (int tail = 0; tail < numsSize; tail++) {
        if (ret > (numsSize - head))
            break;
        update_hash(h, nums[tail], false);
        while (find_hash(h, nums[tail]) > k) {
            update_hash(h, nums[head], true);
            head++;
        }
        int cur_len = tail - head + 1;
        ret = (ret > cur_len ? ret : cur_len);
    }

    dinit_hash(h);
    return ret;
}
