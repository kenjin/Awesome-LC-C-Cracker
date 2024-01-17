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

bool uniqueOccurrences(int* arr, int arrSize)
{
    hash_t h1 = {.size = arrSize, .nodes = calloc(arrSize, sizeof(node_t))};
    for (int i = 0; i < arrSize; i++) {
        if (!find_update_hash(h1, arr[i]))
            add_hash(h1, arr[i]);
    }

    bool ret = true;
    hash_t h2 = {.size = arrSize, .nodes = calloc(arrSize, sizeof(node_t))};
    for (int i = 0; i < h1.size; i++) {
        int val = h1.nodes[i].freq;
        if (val) {
            if (find_update_hash(h2, val)) {
                ret = false;
                break;
            } else {
                add_hash(h2, val);
            }
        }
    }

    free(h1.nodes);
    free(h2.nodes);
    return ret;
}
