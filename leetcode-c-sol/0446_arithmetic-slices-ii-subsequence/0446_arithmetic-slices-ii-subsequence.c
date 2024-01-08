typedef struct __slist {
    long long diff;
    int ctr;
    struct __slist *next;
} slist_t;

typedef struct __hash_ctx {
    int size;
    slist_t *bucket;
} hash_ctx_t;

static inline int do_hash(hash_ctx_t ctx, long long val)
{
    int hash = val % ctx.size;
    return hash < 0 ? hash + ctx.size : hash;
}

static slist_t* find_hash(hash_ctx_t ctx, long long target)
{
    int id = do_hash(ctx, target);
    slist_t *root = ctx.bucket[id].next;
    while (root) {
        if (root->diff == target)
            return root;

        root = root->next;
    }
    return NULL;
}

static slist_t* add_hash(hash_ctx_t ctx, long long diff, int ctr)
{
    int id = do_hash(ctx, diff);
    slist_t *new_node = malloc(sizeof(slist_t));
    new_node->next = ctx.bucket[id].next;
    new_node->diff = diff;
    new_node->ctr = ctr;
    ctx.bucket[id].next = new_node;
    return new_node;
}

int numberOfArithmeticSlices(int* nums, int numsSize)
{
    int ret = 0;
    hash_ctx_t *dp = calloc(numsSize, sizeof(hash_ctx_t));

    for (int i = 0; i < numsSize; i++) {
        dp[i].size = numsSize;
        dp[i].bucket = calloc(numsSize, sizeof(slist_t));
    }

    for (int i = 1; i < numsSize; i++) {
        for (int j = 0; j < i; j++) {
            long long diff = (long long)nums[i] - nums[j];
            slist_t *curr = find_hash(dp[i], diff);
            // Create first node with diff value
            if (!curr) {
                curr = add_hash(dp[i], diff, 0);
            }

            slist_t *prev = find_hash(dp[j], diff);
            if (!prev) {
                // Update second node with diff value.
                curr->ctr += 1;
            } else {
                // existence of the previous node indicates that we have found the third element
                // 1. update the counter of current node
                // 2. Add counter to the result.
                curr->ctr += prev->ctr + 1;
                ret += prev->ctr;
            }
        }
    }

    // Free resource
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < dp[i].size; j++) {
            slist_t *node = dp[i].bucket[j].next;
            while (node) {
                slist_t *tmp = node;
                node = node->next;
                free(tmp);
            }
        }
        free(dp[i].bucket);
    }
    free(dp);

    return ret;
}

