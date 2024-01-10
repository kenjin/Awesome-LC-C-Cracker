typedef struct __infect_node {
    char visited;
    int val;
    int infect_time;
    struct __infect_node *parent;
    struct __infect_node *left;
    struct __infect_node *right;
} INNODE;

typedef struct __queue
{
    int size;
    int cur;
    int front;
    int rear;
    INNODE **p;
} QUEUE;

QUEUE* createq(int size)
{
    QUEUE *obj = malloc(sizeof(QUEUE));
    obj->size = size;
    obj->cur = 0;
    obj->front = 0;
    obj->rear = -1;
    obj->p = malloc(sizeof(INNODE *)*size);
    return obj;
}

void destroyq(QUEUE *obj)
{
    free(obj->p);
    free(obj);
}

bool is_emptyq(QUEUE *obj)
{
    return (obj->cur == 0);
}

void addq(QUEUE *obj, INNODE *node)
{
    obj->rear = (obj->rear+1) % obj->size;
    obj->p[obj->rear] = node;
    obj->cur++;
}

INNODE* delq(QUEUE *obj)
{
    INNODE *ret = obj->p[obj->front];
    obj->front = (obj->front+1) % obj->size;
    obj->cur--;
    return ret;
}

static INNODE* traverse(struct TreeNode *root, int start, INNODE *p, INNODE **target, int *total)
{
    if (!root)
        return NULL;

    INNODE *node = calloc(1, sizeof(INNODE));
    if (p) {
        node->parent = p;
    }
    node->val = root->val;
    node->left = traverse(root->left, start, node, target, total);
    node->right = traverse(root->right, start, node, target, total);

    if (root->val == start)
        *target = node;

    (*total)++;
    return node;
}

int amountOfTime(struct TreeNode* root, int start)
{
    int total = 0;
    INNODE *target;
    // Traverse the tree and create the relationship between nodes
    traverse(root, start , NULL, &target, &total);
    // BFS
    QUEUE *q = createq(total);
    addq(q, target);
    target->visited = 1;
    target->infect_time = 0;
    int ret = 0;
    while (!is_emptyq(q)) {
        INNODE *cur = delq(q);
        ret = cur->infect_time;
        if (cur->parent && !cur->parent->visited) {
            cur->parent->infect_time = cur->infect_time + 1;
            cur->parent->visited = 1;
            addq(q, cur->parent);
        }

        if (cur->left && !cur->left->visited) {
            cur->left->infect_time = cur->infect_time + 1;
            cur->left->visited = 1;
            addq(q, cur->left);
        }

        if (cur->right && !cur->right->visited) {
            cur->right->infect_time = cur->infect_time + 1;
            cur->right->visited = 1;
            addq(q, cur->right);
        }
    }

    destroyq(q);
    return ret;
}
