typedef struct nodeInfo
{
	int val;
	int ctr;
	struct nodeInfo *right;
	struct nodeInfo *left;
} NODE;


typedef struct 
{
	int k;
	NODE *list;
} KthLargest;

int searchNode(NODE *root, int k, int level)
{
	if (root == NULL)
	{
		return -1;
	}
	int rightChildCtr = (root->right != NULL) ? root->right->ctr : 0;
	int leftChildCtr = (root->left != NULL) ? root->left->ctr : 0;
	int rootDuplicate = root->ctr - rightChildCtr - leftChildCtr;

	if (rightChildCtr+1 <= k && k <= rightChildCtr+rootDuplicate)
	{
		return root->val;
	} else if (k <= rightChildCtr)
	{
		return searchNode(root->right, k, level+1);
	} else
	{
		return searchNode(root->left, k-rightChildCtr-rootDuplicate, level+1);
	}
}

NODE* insertNode(NODE *root, int val)
{
	if (root == NULL)
	{
		NODE *newNode = malloc(sizeof(NODE));
		newNode->val = val;
		newNode->ctr = 1;
		newNode->left = newNode->right = NULL;
		return newNode;
	}
	if (val > root->val)
	{
		root->right = insertNode(root->right, val);
	} else if (val < root->val)
	{
		root->left = insertNode(root->left, val);
	}
	root->ctr++;
	return root;
}


KthLargest* kthLargestCreate(int k, int* nums, int numsSize) 
{
	KthLargest *obj = malloc(sizeof(KthLargest));
	obj->k = k;    
	obj->list = NULL;
	for (int i = 0; i < numsSize; i++)
	{
		obj->list = insertNode(obj->list, nums[i]);
	}
	return obj;
}

void freeBST(NODE *root)
{
	if (root == NULL)
	{
		return;
	}
	freeBST(root->right);
	freeBST(root->left);
	free(root);
}

int kthLargestAdd(KthLargest* obj, int val) 
{
	obj->list = insertNode(obj->list, val);
	return searchNode(obj->list, obj->k, 0);
}

void kthLargestFree(KthLargest* obj) 
{
	freeBST(obj->list);
	free(obj);
}

/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);

 * kthLargestFree(obj);
 */
