#define INFO_SIZE_UNIT 500

typedef struct TreeNode NODE;
typedef struct
{
	int val;
	int pos;
	int lv;
}INFO;


void traversal(NODE *root, int pos, int level, INFO **data, int *dataCtr)
{
	if (root == NULL)
	{
		return;
	}

	traversal(root->left, pos-1, level+1, data, dataCtr);
	// Add info
	(*data)[*dataCtr].val = root->val;
	(*data)[*dataCtr].pos = pos;
	(*data)[*dataCtr].lv = level;
	*dataCtr += 1;
	if (0 == *dataCtr % INFO_SIZE_UNIT)
	{
		*data = realloc(*data, sizeof(INFO)*(*dataCtr + INFO_SIZE_UNIT));
	}

	traversal(root->right, pos+1, level+1, data, dataCtr);
}

int compare(void *a, void *b)
{
	INFO *n1 = (INFO *)a;
	INFO *n2 = (INFO *)b;

	if (n1->pos == n2->pos)
	{
		return (n1->lv == n2->lv ? n1->val - n2->val : n1->lv - n2->lv);
	}
	return n1->pos - n2->pos;
}

int** verticalTraversal(NODE* root, int* returnSize, int** returnColumnSizes)
{
	INFO *data = malloc(sizeof(INFO)*INFO_SIZE_UNIT);
	int dataCtr = 0;
	traversal(root, 0, 0, &data, &dataCtr);

	qsort(data, dataCtr, sizeof(INFO), compare);

	int **ret = malloc(sizeof(int*));
	*returnColumnSizes = malloc(sizeof(int));

	// The tree must has "1" nodes
	ret[0] = malloc(sizeof(int));
	(*returnColumnSizes)[0] = 1;
	ret[0][0] = data[0].val;
	int retCtr = 1;    
	for (int i = 1; i < dataCtr; i++)
	{
		if (data[i].pos == data[i-1].pos)
		{
			int tmp = retCtr-1;            
			ret[tmp] = realloc(ret[tmp], sizeof(int)*((*returnColumnSizes)[tmp] + 1));            
			ret[tmp][(*returnColumnSizes)[tmp]] = data[i].val;
			(*returnColumnSizes)[tmp] += 1;
		} else
		{
			ret = realloc(ret, sizeof(int *)*(retCtr+1));
			*returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*(retCtr+1));                
			ret[retCtr] = malloc(sizeof(int));
			(*returnColumnSizes)[retCtr] = 1;
			ret[retCtr][0] = data[i].val;
			retCtr ++;            
		}
	}

	*returnSize = retCtr;
	return ret;
}

