/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define MAX(a, b) (a > b ? a : b)

typedef struct TreeNode NODE;
typedef struct __data {
    NODE *ptr;
    int idx;
} DATA;

typedef struct __queue {
    int size;
    int cur;
    int front;
    int rear;
    DATA *d;
} QUEUE;

static QUEUE *createq(int size)
{
    QUEUE *obj = malloc(sizeof(QUEUE));
    obj->size = size;
    obj->cur = 0;
    obj->front = 0;
    obj->rear = -1;
    obj->d = malloc(sizeof(DATA) * size);
    return obj;
}

static inline void destroyq(QUEUE *obj)
{
    free(obj->d);
    free(obj);
}

static inline int get_qsize(QUEUE *obj)
{
    return obj->cur;
}

static inline bool is_emptyq(QUEUE *obj)
{
    return (obj->cur == 0);
}

static inline void addq(QUEUE *obj, NODE *n, int idx)
{
    obj->rear = (obj->rear + 1) % obj->size;
    obj->d[obj->rear].ptr = n;
    obj->d[obj->rear].idx = idx;
    obj->cur++;
}

static inline DATA delq(QUEUE *obj)
{
    DATA ret = obj->d[obj->front];
    obj->front = (obj->front + 1) % obj->size;
    obj->cur--;
    return ret;
}

static int count_node(NODE *root)
{
    if (!root)
        return 0;
    return count_node(root->left) + count_node(root->right) + 1;
}

#define CHECK_CHILD(q, n, idx)              \
    {                                       \
        if (n->left)                        \
            addq(q, n->left, idx * 2);      \
        if (n->right)                       \
            addq(q, n->right, idx * 2 + 1); \
    }

int widthOfBinaryTree(struct TreeNode *root)
{
    int ret = 0;
    if (!root)
        goto out;

    QUEUE *q = createq(count_node(root));
    addq(q, root, 1);
    while (!is_emptyq(q)) {
        int cnt = get_qsize(q);
        DATA cur = delq(q);
        /* Reset the index if we only have one node in current level to avoid
         * int overflow problem */
        if (cnt == 1)
            cur.idx = 1;

        int start = cur.idx, end = start;
        CHECK_CHILD(q, cur.ptr, end);
        while (--cnt) {
            cur = delq(q);
            end = cur.idx;
            CHECK_CHILD(q, cur.ptr, end);
        }
        ret = MAX(ret, (end - start + 1));
    }

    destroyq(q);
out:
    return ret;
}
