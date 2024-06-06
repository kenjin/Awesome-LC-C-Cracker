#define MINUS (-1)
#define PLUS (1)

typedef struct {
    int key;
    int ctr;
} hash_item_t;

typedef struct {
    hash_item_t* h;
    int sz;
} hash_table_t;

static int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

static inline void free_hash_table(hash_table_t ht) { free(ht.h); }

static int find_hash(hash_table_t ht, int target) {
    int idx = target % ht.sz;
    while (ht.h[idx].key != -1) {
        if (ht.h[idx].key == target)
            return ht.h[idx].ctr;
        idx = (idx + 1) % ht.sz;
    }
    return 0;
}

static void update_hash(hash_table_t ht, int target, int val) {
    int idx = target % ht.sz;
    while (ht.h[idx].key != -1) {
        if (ht.h[idx].key == target)
            break;
        idx = (idx + 1) % ht.sz;
    }
    ht.h[idx].key = target;
    ht.h[idx].ctr += val;
}

bool isNStraightHand(int* hand, int hand_size, int W) {
    if (hand_size % W != 0)
        return false;

    qsort(hand, hand_size, sizeof(int), compare);

    hash_table_t ht = {.h = malloc(sizeof(hash_item_t) * (hand_size + 1)),
                       .sz = hand_size + 1};
    for (int i = 0; i < ht.sz; i++) {
        ht.h[i].key = -1;
        ht.h[i].ctr = 0;
    }

    for (int i = 0; i < hand_size; ++i)
        update_hash(ht, hand[i], PLUS);

    for (int i = 0; i < hand_size; ++i) {
        if (find_hash(ht, hand[i])) {
            update_hash(ht, hand[i], MINUS);
            for (int j = 1; j < W; j++) {
                if (!find_hash(ht, hand[i] + j)) {
                    free_hash_table(ht);
                    return false;
                }
                update_hash(ht, hand[i] + j, MINUS);
            }
        }
    }
    free_hash_table(ht);
    return true;
}
