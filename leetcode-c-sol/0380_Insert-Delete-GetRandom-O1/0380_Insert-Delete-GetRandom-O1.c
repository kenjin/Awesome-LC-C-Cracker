// At most 2 * 105 calls will be made to insert, remove, and getRandom.
#define HASH_TABE_SIZE (200001)

typedef struct __node
{
    int key;
    int idx;
    struct __node *next;
} node_t;

typedef struct 
{
    int size;
    /* Hash table for insert/delete */
    node_t *bucket;
    /* Array for random access */
    int *arr;
    int arr_tail;
} RandomizedSet;

static inline int do_hash(RandomizedSet *obj, int val)
{
    int idx = val % obj->size;
    return (idx < 0 ? idx + obj->size : idx);
}

/* Assmue the val must exist */
static void update_idx_to_hash(RandomizedSet *obj, int val, int new_idx)
{
    int hashIdx = do_hash(obj, val);   
    node_t *root = obj->bucket[hashIdx].next;
    while (root) {
        if (root->key == val) {
            root->idx = new_idx;
            return;
        }
        root = root->next;
    }
}

static bool find_hash(RandomizedSet *obj, int val)
{
    int hash_idx = do_hash(obj, val);
    node_t *root = obj->bucket[hash_idx].next;
    while (root) {
        if (root->key == val)
            return true;
        root = root->next;
    }
    return false;
}

RandomizedSet* randomizedSetCreate() 
{
    RandomizedSet* obj = malloc(sizeof(RandomizedSet));
    obj->size = HASH_TABE_SIZE;
    obj->bucket = calloc(HASH_TABE_SIZE, sizeof(node_t));
    obj->arr = calloc(HASH_TABE_SIZE, sizeof(int));
    obj->arr_tail = -1;
    srand(time(NULL));
    return obj;
}

/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
bool randomizedSetInsert(RandomizedSet* obj, int val) 
{
    /* Already in the set */
    if (find_hash(obj, val))
        return false;

    /* Update array at first, so we can get position idx */
    obj->arr_tail += 1;
    obj->arr[obj->arr_tail] = val;
    
    /* Update Hash */
    int hash_idx = do_hash(obj, val);   
    node_t *new_node = malloc(sizeof(node_t));
    new_node->key = val;
    new_node->idx = obj->arr_tail; /* record the position in array */
    new_node->next = obj->bucket[hash_idx].next;
    obj->bucket[hash_idx].next = new_node;
    return true;
}

/** Removes a value from the set. Returns true if the set contained the specified element. */
bool randomizedSetRemove(RandomizedSet* obj, int val) 
{
    /* Already in the set */
    if (!find_hash(obj, val))
        return false;

    int hash_idx = do_hash(obj, val);
    /* Remove the val from the first of bucket*/
    node_t **indir = &(obj->bucket[hash_idx].next);
    while (*indir && (*indir)->key != val) {
       indir = &(*indir)->next;
    }
   int arr_pos = (*indir)->idx;
   node_t *fnode = *indir;
   *indir = (*indir)->next;
   free(fnode);
    
    /* Remove from array*/
    /* Swap the deleted element and tail element */
    if (obj->arr_tail != arr_pos) {
        int tmp = obj->arr[obj->arr_tail];
        obj->arr[obj->arr_tail] = obj->arr[arr_pos];
        obj->arr[arr_pos] = tmp;
        update_idx_to_hash(obj, tmp, arr_pos);
        obj->arr_tail -= 1;
    } else {
        obj->arr_tail -= 1;
    }
    return true;
}

/** Get a random element from the set. */
int randomizedSetGetRandom(RandomizedSet* obj) 
{
    int r = rand() % (obj->arr_tail+1);
    return obj->arr[r];
}

void randomizedSetFree(RandomizedSet* obj) 
{
    for (int i = 0; i < obj->size; i++){
        node_t *cur = obj->bucket[i].next;
        while (cur) {
            node_t *del = cur; 
            cur = cur->next;
            free(del);
        }
    }
    free(obj->bucket);
    free(obj->arr);
    free(obj);    
}
