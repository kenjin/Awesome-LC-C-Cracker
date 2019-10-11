/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct TreeNode NODE;
typedef struct hashT HASH;

struct hashInfo
{
	int used;
	int val;   
};

struct hashT
{
	int size;
	int mod;
	struct hashInfo *arr;
};

int hash(HASH *obj, int key) 
{
	int r = key % obj->mod;
	return r < 0 ? r + obj->size : r;
}

HASH* createHash(int size)
{
	HASH *obj = malloc(sizeof(HASH));
	obj->size = size;
	obj->mod = size;
	obj->arr = calloc(size, sizeof(struct hashInfo));
	return obj;
}

void addHash(HASH *ht, int key) 
{
	int index = hash(ht, key);
	while (ht->arr[index].used) 
	{
		index++;
		index %= ht->size;
	}
	ht->arr[index].used = 1;
	ht->arr[index].val = key;
}

bool findHash(HASH *ht, int target) 
{
	int index = hash(ht, target);
	while (ht->arr[index].used) 
	{
		if (ht->arr[index].val == target) 
		{
			return true;
		}
		index++;
		index %= ht->size;
	}
	return false;
}

void releaseHash(HASH *ht)
{
	free(ht->arr);
	free(ht);
}

int countNodes(NODE *root)
{
	if (root == NULL)
	{
		return 0;
	}

	return countNodes(root->left) + countNodes(root->right) + 1;
}

bool traverseBST(NODE *root, HASH *h, int k)
{
	if (root == NULL)
	{
		return false;
	}
	if (findHash(h, k - root->val))
	{
		return true;
	}

	addHash(h, root->val);

	if (false == traverseBST(root->left, h, k) &&
			false == traverseBST(root->right, h, k))
	{
		return false;        
	}
	return true;    
}

bool findTarget(struct TreeNode* root, int k)
{
	if (root == NULL)
	{
		return false;
	}
	// decide the size of hash table
	int count = countNodes(root);
	HASH *h = createHash(count+1);
	// Check two sum
	bool ret = traverseBST(root, h, k);
	releaseHash(h);
	return ret;
}


