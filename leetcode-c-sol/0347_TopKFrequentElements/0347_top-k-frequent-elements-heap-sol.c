typedef struct {
    int num;
    int cnt;
} bucket_t;

typedef struct {
    bucket_t *buckets;
    int *heap; /* a max heap store the idx of bucket */
    int b_size;
    int h_size;
} sol_ctx_t;

#define XOR_SWAP(a, b) do { \
    a = a ^ b; b = a ^ b; a = a ^ b; \
} while (0)

static sol_ctx_t* create_hash(int sz)
{
    sol_ctx_t *ctx = calloc(1, sizeof(sol_ctx_t));
    ctx->b_size = sz;
    ctx->buckets = calloc(sz, sizeof(bucket_t));
    ctx->heap = malloc(sz * sizeof(int));
    return ctx;
}

static void destroy_hash(sol_ctx_t *ctx)
{
    free(ctx->heap);
    free(ctx->buckets);
    free(ctx);
}

static inline int do_hash(sol_ctx_t *ctx, int target)
{
    int idx = target % ctx->b_size;
    return idx < 0 ? idx + ctx->b_size : idx;
}

static void update_hash(sol_ctx_t *ctx, int target)
{
    int idx = do_hash(ctx, target);
    if (ctx->buckets[idx].cnt != 0) {
        if (target == ctx->buckets[idx].num) {
            ctx->buckets[idx].cnt++;
            return;
        }
        idx = (idx + 1) % ctx->b_size;
    }

    ctx->buckets[idx].num = target;
    ctx->buckets[idx].cnt++;
    ctx->heap[ctx->h_size] = idx;
    ctx->h_size++;
}

static void heapify(sol_ctx_t *ctx, int idx)
{
    int l_idx = (idx << 1) + 1, r_idx = (idx << 1) + 2, max_idx = idx;
    if (l_idx < ctx->h_size &&
            ctx->buckets[ctx->heap[l_idx]].cnt > ctx->buckets[ctx->heap[max_idx]].cnt)
        max_idx = l_idx;

    if (r_idx < ctx->h_size &&
            ctx->buckets[ctx->heap[r_idx]].cnt > ctx->buckets[ctx->heap[max_idx]].cnt)
        max_idx = r_idx;

    if (max_idx != idx) {
        XOR_SWAP(ctx->heap[idx], ctx->heap[max_idx]);
        heapify(ctx, max_idx);
    }
}

static int del_heap(sol_ctx_t *ctx)
{
    int ret = ctx->buckets[ctx->heap[0]].num;
    ctx->heap[0] = ctx->heap[ctx->h_size - 1];
    ctx->h_size--;
    heapify(ctx, 0);
    return ret;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize)
{
    sol_ctx_t *ctx = create_hash(numsSize);
    for (int i = 0; i < numsSize; i++)
        update_hash(ctx, nums[i]);

    for (int i = ((ctx->h_size - 1) >> 1); i >= 0; i--)
        heapify(ctx, i);

    int *ret = malloc(sizeof(int) * k);
    *returnSize = k;
    for (int i = 0; i < k; i++)
        ret[i] = del_heap(ctx);

    destroy_hash(ctx);
    return ret;
}
