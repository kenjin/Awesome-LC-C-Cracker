#define IS_ODD(val) (val & 0x1)

bool isEvenOddTree(struct TreeNode* root) {
    struct TreeNode **q = malloc(sizeof(struct TreeNode*) * 100000),
                    *prev = NULL;
    int rear = 0, front = 0, lv = 0;
    bool ret = true;
    q[rear++] = root;
    while (front < rear) {
        int sz = rear - front;
        for (int i = 0; i < sz; i++) {
            root = q[front++];
            if (IS_ODD(lv)) {
                // ensure to be an even integer and strictly decreasing order
                if (IS_ODD(root->val) || (prev && prev->val <= root->val)) {
                    ret = false;
                    goto out;
                }
            } else {
                // ensure to be an even integer and strictly increasing order
                if (!IS_ODD(root->val) || (prev && prev->val >= root->val)) {
                    ret = false;
                    goto out;
                }
            }
            if (root->left)
                q[rear++] = root->left;
            if (root->right)
                q[rear++] = root->right;
            prev = root;
        }
        lv ^= 0x1;
        prev = NULL;
    }
out:
    free(q);
    return ret;
}
