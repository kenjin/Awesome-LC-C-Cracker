/***

Approach: Prefix Sum + Hash

- Continuously calculate the prefix sum. If we find that the prefix sum of two elements is equal, it means we have a zero-sum consecutive sublist between them.
- We need to allocate a dummy node to handle the case where the prefix sum is zero.
- Use a hash table to quickly find the list node.

head = [1, 2, -3, 3, 1]
prefix_sum = [1, 3, 0, 3, 4] => Remove 3rd and 4th node. (2nd->next = 5th)
                    ^  ^

head = [1, 2, 3, -6]
prefix_sum = [1, 3, 6, 0] => 0 Remove the entire linked list. (dummy->next = NULL)

***/

#define HASH_MOD (1000)
typedef struct {
    struct ListNode *node;
    int sum;
} data_t;

static inline int do_hash(int val)
{
   int hidx = val % HASH_MOD;
   return (hidx < 0 ? hidx + HASH_MOD : hidx);
}

static void update_hash(data_t *list_set, struct ListNode *node, int sum)
{
    int hidx = do_hash(sum);
    while (list_set[hidx].node) {
        // if find the same sum, update the latest node
        if (list_set[hidx].sum == sum)
            break;
        hidx = (hidx + 1) % HASH_MOD;
    }
    list_set[hidx].node = node;
    list_set[hidx].sum = sum;
}

static struct ListNode* find_hash(data_t *list_set, int sum)
{
    int hidx = do_hash(sum);
    while (list_set[hidx].node) {
        if (list_set[hidx].sum == sum)
            return list_set[hidx].node;
        hidx = (hidx + 1) % HASH_MOD;
    }
    assert(list_set[hidx].node);
    return NULL;
}

struct ListNode* removeZeroSumSublists(struct ListNode* head)
{
    data_t list_set[HASH_MOD] = {0};
    struct ListNode *dummy = malloc(sizeof(struct ListNode));
    dummy->next = head;
    dummy->val = 0;
    int sum = 0;
    for (struct ListNode *cur = dummy; cur; cur = cur->next) {
        sum += cur->val;
        update_hash(list_set, cur, sum);
    }

    sum = 0;
    for (struct ListNode *cur = dummy; cur; cur = cur->next) {
        sum += cur->val;
        cur->next = (find_hash(list_set, sum))->next;
    }

    struct ListNode *ret = dummy->next;
    free(dummy);
    return ret;
}
