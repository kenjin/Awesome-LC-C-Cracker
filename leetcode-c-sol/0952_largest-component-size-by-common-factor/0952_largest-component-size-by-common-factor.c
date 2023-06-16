
#define MAX(a, b) (a > b ? a : b)

typedef struct {
    int val;
    int com_sz;
} data_t;

typedef struct {
    data_t *d;
    int size;
} hash_t;

static inline hash_t *hash_create(int size)
{
    hash_t *obj = malloc(sizeof(hash_t));
    obj->size = size;
    obj->d = calloc(size, sizeof(data_t));
    return obj;
}

static inline void hash_release(hash_t *h)
{
    free(h->d);
    free(h);
}

static void hash_add(hash_t *h, int val)
{
    int hidx = val % h->size;
    while (h->d[hidx].com_sz)
        hidx = (hidx + 1) % h->size;

    h->d[hidx].val = val;
    h->d[hidx].com_sz = 1;
}

static int hash_update(hash_t *h, int val)
{
    int hidx = val % h->size;
    while (h->d[hidx].val != val)
        hidx = (hidx + 1) % h->size;

    h->d[hidx].com_sz += 1;
    return h->d[hidx].com_sz;
}

/* Return the idnex of root */
static int set_find(int *set, int target)
{
    if (set[target] < 0)
        return target;

    int ret = set_find(set, set[target]);
    /* compress set */
    set[target] = ret;
    return ret;
}

static void set_union(int *set, int target, int cur)
{
    int r1_idx = set_find(set, target);
    int r2_idx = set_find(set, cur);
    if (r1_idx == r2_idx)
        return;

    if (set[r1_idx] <= set[r2_idx]) {
        set[r1_idx] += set[r2_idx];
        set[r2_idx] = r1_idx;
    } else {
        set[r2_idx] += set[r1_idx];
        set[r1_idx] = r2_idx;
    }
}

int largestComponentSize(int *A, int ASize)
{
    int max = A[0];
    for (int i = 1; i < ASize; i++)
        max = MAX(max, A[i]);

    int *set = malloc(sizeof(int) * (max + 1));
    for (int i = 0; i < max + 1; i++)
        set[i] = -1;

    hash_t *h = hash_create(max + 1);
    for (int i = 0; i < ASize; i++)
        hash_add(h, A[i]);

    for (int i = 0; i < ASize; i++) {
        int num = sqrt(A[i]);
        for (int cur = 2; cur <= num; cur++) {
            if (A[i] % cur == 0) {
                set_union(set, A[i], cur);
                set_union(set, A[i], A[i] / cur);
            }
        }
    }

    int ret = 0;
    for (int i = 0; i < ASize; i++) {
        int cur_ret = hash_update(h, set_find(set, A[i]));
        ret = MAX(ret, cur_ret);
    }

    hash_release(h);
    free(set);
    return (ret - 1);
}
