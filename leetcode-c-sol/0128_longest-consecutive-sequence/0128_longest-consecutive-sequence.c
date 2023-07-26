typedef struct _list{
    int num;
    int seq; // consecutive seq
    struct _list *next;
} list_t;

typedef struct {
    list_t head;
} bucket_t;

typedef struct {
    bucket_t *buckets;
    int size;
} sol_ctx_t;

static sol_ctx_t* create_hash(int sz)
{
    sol_ctx_t *ctx = calloc(1, sizeof(sol_ctx_t));
    ctx->size = sz;
    ctx->buckets = calloc(sz, sizeof(bucket_t));
    return ctx;
}

static void destroy_hash(sol_ctx_t *ctx)
{
    for (int i = 0; i < ctx->size; i++) {
        list_t *root = ctx->buckets[i].head.next;
        while (root) {
            list_t *tmp = root->next;
            free(root);
            root = tmp;
        }
    }
    free(ctx->buckets);
    free(ctx);
}

static inline int do_hash(sol_ctx_t *ctx, int target)
{
    int idx = target % ctx->size;
    return idx < 0 ? idx + ctx->size : idx;
}

static inline list_t* find_hash(sol_ctx_t *ctx, int target)
{
    int idx = do_hash(ctx, target);
    list_t *root = ctx->buckets[idx].head.next;
    while (root) {
        if (target == root->num) {
            return root;
        }
        root = root->next;
    }
    return NULL;
}

static inline void add_hash(sol_ctx_t *ctx, int target)
{
    int idx = do_hash(ctx, target);
    list_t *new_node = calloc(1, sizeof(list_t));
    list_t *tmp = ctx->buckets[idx].head.next;
    new_node->num = target;
    new_node->seq = 1;
    new_node->next = tmp;
    ctx->buckets[idx].head.next = new_node;
}

int longestConsecutive(int* nums, int numsSize){
    sol_ctx_t *ctx = create_hash(numsSize);
    int max = 0;
    for (int i = 0; i < numsSize; i++) {
        int target = nums[i];
        if (NULL != find_hash(ctx, target)) {
            continue;
        }

        add_hash(ctx, target);
        // Update left/right boundry:
        //
        //  -- l --     -- r  -- 
        // [4, 5, 6] 7 [8, 9, 10]
        //           |
        //          new
        list_t *l = find_hash(ctx, target - 1);
        list_t *r = find_hash(ctx, target + 1);

        int seq_l = (l == NULL? 0 : l->seq);
        int seq_r = (r == NULL? 0 : r->seq);
        int total = seq_l + seq_r + 1;

        // In genral, must return the node
        l = find_hash(ctx, target - seq_l /* (target - 1) -  seq_l + 1 */);
        r = find_hash(ctx, target + seq_r /* (target + 1) +  seq_r - 1 */);
        l->seq = total;
        r->seq = total;
        max = (max > total ? max : total);
    }
    destroy_hash(ctx);
    return max;
}
