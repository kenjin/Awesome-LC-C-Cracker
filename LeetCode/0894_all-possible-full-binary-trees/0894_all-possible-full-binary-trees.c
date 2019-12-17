
struct TreeNode** allPossibleFBTHelper(int N, int* returnSize, struct TreeNode ***fbt, int *fbtSize) 
{
	struct TreeNode **ret = malloc(sizeof(struct TreeNode*));
	*returnSize = 0;

	if (N == 1) 
	{
		struct TreeNode *root = calloc(1, sizeof(struct TreeNode));
		ret = realloc(ret, sizeof(struct TreeNode) * ((*returnSize) + 1));
		ret[*returnSize] = root;
		*returnSize += 1;
		return ret;
	}

	for (int x = 1; x <= N - 2; x += 2) 
	{
		int lSize = fbtSize[x], rSize = fbtSize[N-x-1];
		for (int i = 0; i < lSize; i++) 
		{
			for (int j = 0; j < rSize; j++) 
			{
				struct TreeNode *root = calloc(1, sizeof(struct TreeNode));
				root->left = fbt[x][i];
				root->right = fbt[N-x-1][j];
				ret = realloc(ret, sizeof(struct TreeNode)*((*returnSize) + 1));
				ret[*returnSize] = root;
				*returnSize += 1;
			}
		}
	}
	return ret;    
}

struct TreeNode** allPossibleFBT(int N, int* returnSize)
{
	if ((N % 2) == 0)
	{
		*returnSize = 0;
		return NULL;
	}

	struct TreeNode **fbt[21];
	int fbtSize[21] = {0};
	for (int i = 1; i <= N; i+=2)
	{
		int tmpSize = 0;
		fbt[i] = allPossibleFBTHelper(i, &tmpSize, fbt, fbtSize);
		fbtSize[i] = tmpSize;
	}

	*returnSize = fbtSize[N];    
	return fbt[N];
}
