#define INFO_SIZE_UNIT 5000

typedef struct TreeNode NODE;
typedef struct {
    int val;
    int pos;
    int lv;
} INFO;

void traversal(NODE *root, int pos, int level, INFO **data, int *data_ctr)
{
    if (!root)
        return;

    traversal(root->left, pos - 1, level + 1, data, data_ctr);
    /* Add info */
    (*data)[*data_ctr].val = root->val;
    (*data)[*data_ctr].pos = pos;
    (*data)[*data_ctr].lv = level;
    *data_ctr += 1;
    if (0 == *data_ctr % INFO_SIZE_UNIT)
        *data = realloc(*data, sizeof(INFO) * (*data_ctr + INFO_SIZE_UNIT));

    traversal(root->right, pos + 1, level + 1, data, data_ctr);
}

int compare(void *a, void *b)
{
    INFO *n1 = (INFO *) a;
    INFO *n2 = (INFO *) b;
    if (n1->pos == n2->pos)
        return (n1->lv == n2->lv ? n1->val - n2->val : n1->lv - n2->lv);
    return n1->pos - n2->pos;
}

int **verticalTraversal(NODE *root, int *returnSize, int **returnColumnSizes)
{
    INFO *data = malloc(sizeof(INFO) * INFO_SIZE_UNIT);
    int data_ctr = 0;
    traversal(root, 0, 0, &data, &data_ctr);

    qsort(data, data_ctr, sizeof(INFO), compare);

    int **ret = malloc(sizeof(int *));
    *returnColumnSizes = malloc(sizeof(int));

    ret[0] = malloc(sizeof(int));
    (*returnColumnSizes)[0] = 1;
    ret[0][0] = data[0].val;
    int ret_ctr = 1;
    for (int i = 1; i < data_ctr; i++) {
        if (data[i].pos == data[i - 1].pos) {
            int tmp = ret_ctr - 1;
            ret[tmp] = realloc(ret[tmp],
                               sizeof(int) * ((*returnColumnSizes)[tmp] + 1));
            ret[tmp][(*returnColumnSizes)[tmp]] = data[i].val;
            (*returnColumnSizes)[tmp] += 1;
        } else {
            ret = realloc(ret, sizeof(int *) * (ret_ctr + 1));
            *returnColumnSizes =
                realloc(*returnColumnSizes, sizeof(int) * (ret_ctr + 1));
            ret[ret_ctr] = malloc(sizeof(int));
            (*returnColumnSizes)[ret_ctr] = 1;
            ret[ret_ctr][0] = data[i].val;
            ret_ctr++;
        }
    }

    *returnSize = ret_ctr;
    return ret;
}