typedef struct __node {
    int val;
    int freq;
} node_t;

typedef struct __hash {
    int size;
    node_t *nodes;
} hash_t;

#define MAX(a,b) (a > b ? a : b)

static inline int do_hash(hash_t h, int val)
{
    int ret = val % h.size;
    return (ret < 0 ? ret + h.size : ret);
}

static bool find_update_hash(hash_t h, int val, int *max)
{
    int hidx = do_hash(h, val);
    while (h.nodes[hidx].val != 0){
        if (h.nodes[hidx].val == val) {
            h.nodes[hidx].freq += 1;
            *max = MAX(*max, h.nodes[hidx].freq);
            return true;
        }
        hidx = (hidx + 1) % h.size;
    }
    return false;
}

static void add_hash(hash_t h, int val, int *max)
{
    int hidx = do_hash(h, val);
    while (h.nodes[hidx].val != 0) {
        hidx = (hidx + 1) % h.size;
    }

    h.nodes[hidx].val = val;
    h.nodes[hidx].freq = 1;
    *max = MAX(*max, h.nodes[hidx].freq);
}

int maxFrequencyElements(int* nums, int numsSize)
{
    hash_t h = {.size = numsSize, .nodes = calloc(numsSize, sizeof(node_t))};
    int max = 0;
    for (int i = 0; i < numsSize; i++) {
        if (!find_update_hash(h, nums[i], &max))
            add_hash(h, nums[i], &max);
    }

    int ret = 0;
    for (int i = 0; i < h.size; i++) {
        if (h.nodes[i].freq == max) {
            ret += max;
        }
    }

    return ret;
}
