
int findBottomLeftValue(struct TreeNode* root) {
    struct TreeNode** q = malloc(sizeof(struct TreeNode*) * 10000);
    int rear = 0, front = 0;
    q[rear++] = root;
    while (front < rear) {
        int sz = rear - front;
        for (int i = 0; i < sz; i++) {
            root = q[front++];
            if (root->right)
                q[rear++] = root->right;
            if (root->left)
                q[rear++] = root->left;
        }
    }
    free(q);
    return root->val;
}
