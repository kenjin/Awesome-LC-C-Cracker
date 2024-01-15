typedef struct __node {
    int val; // 1 <= winneri, loseri <= 10^5, 0 indicates empty node
    int indegree;
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

static bool find_update_hash(hash_t h, int val, int indegree)
{
    int hidx = do_hash(h, val);
    while (h.nodes[hidx].val != 0){
        if (h.nodes[hidx].val == val) {
            h.nodes[hidx].indegree += indegree;
            return true;
        }
        hidx = (hidx + 1) % h.size;
    }
    return false;
}

static void add_hash(hash_t h, int val, int indegree)
{
    int hidx = do_hash(h, val);
    while (h.nodes[hidx].val != 0) {
        hidx = (hidx + 1) % h.size;
    }

    h.nodes[hidx].val = val;
    h.nodes[hidx].indegree = indegree;
}

static int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findWinners(int** matches, int matchesSize, int* matchesColSize, int* returnSize, int** returnColumnSizes)
{
    hash_t h = {.size = matchesSize*2, .nodes = calloc(matchesSize*2, sizeof(node_t))};
    for (int i = 0; i < matchesSize; i++) {
        if (!find_update_hash(h, matches[i][0], 0)) {
            add_hash(h, matches[i][0], 0);
        }
        if (!find_update_hash(h, matches[i][1], 1)) {
            add_hash(h, matches[i][1], 1);
        }
    }

    int **ret = malloc(sizeof(int *)*2);
    ret[0] = malloc(sizeof(int)*h.size);
    ret[1] = malloc(sizeof(int)*h.size);
    int ctr1 = 0, ctr2 = 0;
    for (int i = 0; i < h.size; i++) {
        if (h.nodes[i].val && h.nodes[i].indegree == 0)
            ret[0][ctr1++] = h.nodes[i].val;
        else if (h.nodes[i].val && h.nodes[i].indegree == 1)
            ret[1][ctr2++] = h.nodes[i].val;
    }

    *returnSize = 2;
    *returnColumnSizes = malloc(sizeof(int)*2);
    (*returnColumnSizes)[0] = ctr1;
    (*returnColumnSizes)[1] = ctr2;

    if (ctr1) {
        ret[0] = realloc(ret[0], sizeof(int)*ctr1);
        qsort(ret[0], ctr1, sizeof(int), compare);
    } else {
        free(ret[0]);
    }
    if (ctr2) {
        ret[1] = realloc(ret[1], sizeof(int)*ctr2);
        qsort(ret[1], ctr2, sizeof(int), compare);
    } else {
        free(ret[1]);
    }

    free(h.nodes);
    return ret;
}
