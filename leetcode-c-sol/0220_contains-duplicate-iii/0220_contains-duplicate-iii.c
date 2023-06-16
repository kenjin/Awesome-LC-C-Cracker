typedef struct bstInfo NODE;

struct bstInfo
{
	int val;
	int idx;
	NODE *left;
	NODE *right;
};

NODE* findBST(NODE *root, int key)
{
	if (root == NULL)
	{
		return NULL;
	}

	if (key < root->val)
	{
		return findBST(root->left, key);
	} else if (key > root->val)
	{
		return findBST(root->right, key);
	} else
	{
		return root;
	}
}

NODE* findParent(NODE *root, NODE *target)
{
	/* No Answer */
	if (root == NULL)
	{
		return NULL;        
	}

	if (root->left == target || root->right == target)
	{
		return root;
	} else
	{
		if (root->val < target->val)
		{
			return findParent(root->right, target);
		} else 
		{
			return findParent(root->left, target);
		}
	}
}

NODE* deleteNode(NODE* root, int key)
{
	/* Find Node */
	NODE *target = findBST(root, key);

	if (target != NULL)
	{
		if (target->left == NULL && target->right == NULL)
		{
			/* Case1: No child*/
			NODE *p = findParent(root, target);
			if (p != NULL)
			{
				if (p->right != NULL && p->right == target)
				{
					p->right = NULL;
				} else /* p->left != NULL && p->left == target */
				{
					p->left = NULL;
				}
			}
			free(target);
			/* After free "target", if target and root are the same pointer, can not return ... 
			 * Test case: [0], delete 0
			 */
			/* TODO: Clarify it! */
			if (target == root)
			{
				return NULL;
			}
			/* TODO: END */
		} else if (target->left == NULL || target->right == NULL)
		{
			/* Case2: One child */
			NODE *replaceNode;
			if (target->left == NULL)
			{
				replaceNode = target->right;
			} else  /* target->right == NULL */
			{
				replaceNode = target->left;
			}
			//printf("Case2: replace target %d to %d\n", target->val, replaceNode->val);
			/* replace target to target's child */
			target->val   = replaceNode->val;
			target->left  = replaceNode->left;
			target->right = replaceNode->right;
			free(replaceNode);        
		} else
		{
			/* Case3: Target has two childs case */

			/* Find next first node who is greater than target node */
			NODE *nextOne = target->right;  /* two childs case so right child must exist */
			while (nextOne->left)
			{
				nextOne = nextOne->left;
			}
			int tmp = nextOne->val;
			/* find nextOne's parent to updae link to NULL */
			deleteNode(target, nextOne->val);
			target->val = tmp;            
		} 
	} 

	return root;
}

NODE* containsDuplicateHelper(NODE *root, int val, int t, int *ret)
{
	if (root == NULL)
	{
		NODE *newOne = calloc(1, sizeof(NODE));
		newOne->val = val;
		return newOne;
	}

	// Avoid overflow case
	long diff = (long)(root->val) - (long)(val);
	if (diff <= INT_MAX && diff > INT_MIN &&
			abs((int)diff) <= t)
	{
		*ret = 1;
		return root;
	}

	if (root->val > val)
	{
		root->left = containsDuplicateHelper(root->left, val, t, ret);        
	} else if (root->val < val)
	{
		root->right = containsDuplicateHelper(root->right, val, t, ret);
	} else if (root->val == val && t >= 0)
	{
		*ret = 1;
	}
	return root;
}

void freeBST(NODE *root)
{
	if (root == NULL)
	{
		return;
	}
	freeBST(root->left);
	freeBST(root->right);
	free(root);
}

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int k, int t)
{
	NODE *root = NULL;
	int ctr = 0;
	int ret = 0;
	for (int i = 0; i < numsSize; i++)
	{        
		if (ctr <= k)
		{   
			root = containsDuplicateHelper(root, nums[i], t, &ret);
			ctr++;
		} else
		{ 
			root = deleteNode(root, nums[i-k-1]);
			root = containsDuplicateHelper(root, nums[i], t, &ret);
		}
		if (ret)
		{
			return true;
		}
	}

	freeBST(root);
	return false;
}
