
#define MAX_CACHE_SZ (10 * 1024)
#define VAL_IS_NULL -1

struct cache_item {
    int key;
    int value;
    struct cache_item* prev;
    struct cache_item* next;
};

typedef struct {
    struct cache_item table[MAX_CACHE_SZ];
    size_t size;
    size_t capacity;
    struct cache_item* lru_head;
} LRUCache;

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* cache = calloc(1, sizeof(*cache));
    for (int i = 0; i < MAX_CACHE_SZ; i++) {
        cache->table[i].key = i;
        cache->table[i].value = VAL_IS_NULL;
    }
    cache->capacity = capacity;
    return cache;
}

static void remove_item(LRUCache* cache, struct cache_item* item, bool delete) {
    if (delete)
        cache->table[item->key].value = VAL_IS_NULL;

    // Remove from list
    struct cache_item* prev = item->prev;
    struct cache_item* next = item->next;
    prev->next = next;
    next->prev = prev;
    if (item == cache->lru_head)
        cache->lru_head = next;

    cache->size--;
}

static void add_item(LRUCache* cache, struct cache_item* item) {
    struct cache_item* tail;
    // Circular linked list, so tail is head->prev
    if (cache->lru_head == NULL) {
        item->prev = item;
        item->next = item;
        cache->lru_head = item;
        return;
    }

    tail = cache->lru_head->prev;
    tail->next = item;
    item->prev = tail;
    item->next = cache->lru_head;
    cache->lru_head->prev = item;
}

static void update_lru(LRUCache* cache, int key) {
    struct cache_item* item = &cache->table[key];
    if (cache->table[key].value != VAL_IS_NULL)
        remove_item(cache, item, false);

    cache->size++;
    add_item(cache, item);
}

int lRUCacheGet(LRUCache* cache, int key) {
    int ret = cache->table[key].value;
    if (ret != VAL_IS_NULL)
        update_lru(cache, key);

    return ret;
}

void lRUCachePut(LRUCache* cache, int key, int value) {
    update_lru(cache, key);
    cache->table[key].value = value;
    // Remove least recently used item (lru_head)
    if (cache->size > cache->capacity)
        remove_item(cache, cache->lru_head, true);
}

void lRUCacheFree(LRUCache* cache) { free(cache); }

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);

 * lRUCachePut(obj, key, value);

 * lRUCacheFree(obj);
*/
