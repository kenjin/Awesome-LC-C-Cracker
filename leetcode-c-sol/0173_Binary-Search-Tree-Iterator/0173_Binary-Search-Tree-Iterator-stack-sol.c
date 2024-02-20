
typedef struct {
    struct TreeNode** stack;
    int cur_sz;
} BSTIterator;

static int get_height(struct TreeNode* root) {
    if (!root)
        return 0;
    int r = get_height(root->left);
    int l = get_height(root->right);
    return (r > l ? r : l) + 1;
}

static void push_left_nodes(BSTIterator* obj, struct TreeNode* root) {
    while (root) {
        obj->stack[obj->cur_sz] = root;
        obj->cur_sz += 1;
        root = root->left;
    }
}

BSTIterator* bSTIteratorCreate(struct TreeNode* root) {
    int h = get_height(root);
    BSTIterator* obj = malloc(sizeof(BSTIterator));
    obj->stack = malloc(sizeof(struct TreeNode*) * h);
    obj->cur_sz = 0;
    push_left_nodes(obj, root);

    return obj;
}

int bSTIteratorNext(BSTIterator* obj) {
    obj->cur_sz -= 1;
    struct TreeNode* cur = obj->stack[obj->cur_sz];

    int ret = cur->val;
    push_left_nodes(obj, cur->right);
    return ret;
}

bool bSTIteratorHasNext(BSTIterator* obj) {
    return (obj->cur_sz > 0 ? true : false);
}

void bSTIteratorFree(BSTIterator* obj) {
    free(obj->stack);
    free(obj);
}

