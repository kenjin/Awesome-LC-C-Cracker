static int count_node(struct TreeNode* root)
{
    if (!root)
        return 0;

    return count_node(root->left) + count_node(root->right) + 1;
}

static void update_leaf(struct TreeNode* root, int *leaf, int *leaf_ctr)
{
    if (!root)
        return;

    if (!root->left && !root->right) {
        leaf[*leaf_ctr] = root->val;
        *leaf_ctr += 1;
    }
    update_leaf(root->left, leaf, leaf_ctr);
    update_leaf(root->right, leaf, leaf_ctr);
}

bool leafSimilar(struct TreeNode* root1, struct TreeNode* root2)
{
    int ctr1 = count_node(root1);
    int ctr2 = count_node(root2);
    int *leaf1 = malloc(sizeof(int)*ctr1);
    int *leaf2 = malloc(sizeof(int)*ctr2);

    int lctr1 = 0, lctr2 = 0;
    update_leaf(root1, leaf1, &lctr1);
    update_leaf(root2, leaf2, &lctr2);

    bool ret = true;
    if (lctr1 != lctr2) {
        ret= false;
    } else {
        for (int i = 0; i < lctr1; i++) {
            if (leaf1[i] != leaf2[i]) {
                ret = false;
                break;
            }
        }
    }

    free(leaf1);
    free(leaf2);
    return ret;
}

