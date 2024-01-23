typedef struct __node {
    int val;
    int freq;
} node_t;

typedef struct __hash {
    int size;
    node_t *nodes;
} hash_t;

static inline int do_hash(hash_t h, int val)
{
    int ret = val % h.size;
    return (ret < 0 ? ret + h.size : ret);
}

static bool find_update_hash(hash_t h, int val)
{
    int hidx = do_hash(h, val);
    while (h.nodes[hidx].freq != 0){
        if (h.nodes[hidx].val == val) {
            h.nodes[hidx].freq += 1;
            return true;
        }
        hidx = (hidx + 1) % h.size;
    }
    return false;
}

static void add_hash(hash_t h, int val)
{
    int hidx = do_hash(h, val);
    while (h.nodes[hidx].freq != 0) {
        hidx = (hidx + 1) % h.size;
    }
    h.nodes[hidx].val = val;
    h.nodes[hidx].freq = 1;
}

int minOperations(int* nums, int numsSize)
{
    hash_t h = {.size = numsSize, .nodes = calloc(numsSize, sizeof(node_t))};
    for (int i = 0; i < numsSize; i++) {
        if (!find_update_hash(h, nums[i])) {
            add_hash(h, nums[i]);
        }
    }

    int ret = 0;
    for (int i = 0; i < h.size; i++) {
        // failure case 
        if (h.nodes[i].freq == 1) {
            ret = -1;
            break;
        }

        if (h.nodes[i].freq % 3 == 0)
            ret += (h.nodes[i].freq / 3);
        else // h.nodes[i].freq % 3 == 1(2)
            ret += (h.nodes[i].freq / 3 + 1);
    }
    free(h.nodes);
    return ret;
}
