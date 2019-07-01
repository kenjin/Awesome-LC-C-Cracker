#define MAX(a, b) a > b ? a : b

// An AVL tree data structure
typedef struct AVLTree
{ 
	int key; 
	int idx;
	int height; 
	struct AVLTree *left; 
	struct AVLTree *right;     
}NODE; 


int height(NODE *N) 
{
	return (N == NULL) ? 0 : N->height; 
} 

NODE* newNode(int key, int idx) 
{ 
	NODE* obj = malloc(sizeof(NODE)); 
	obj->key   = key; 
	obj->idx   = idx; 
	obj->height = 1;
	obj->left   = NULL; 
	obj->right  = NULL;     
	return obj;
} 

NODE* rightRotate(NODE *y) 
{ 
	NODE *x = y->left; 
	NODE *T2 = x->right; 

	// Perform rotation 
	x->right = y; 
	y->left = T2; 

	// Update heights 
	y->height = MAX(height(y->left), height(y->right))+1; 
	x->height = MAX(height(x->left), height(x->right))+1; 

	// Return new root 
	return x; 
} 

NODE* leftRotate(NODE *x) 
{ 
	NODE *y = x->right; 
	NODE *T2 = y->left; 

	// Perform rotation 
	y->left = x; 
	x->right = T2; 

	//  Update heights 
	x->height = MAX(height(x->left), height(x->right))+1; 
	y->height = MAX(height(y->left), height(y->right))+1; 

	// Return new root 
	return y; 
} 

// Get Balance factor of node N 
int getBalance(NODE *N) 
{
	return (N == NULL) ? 0 : height(N->left) - height(N->right); 
} 

NODE* insert(NODE* node, int key, int idx) 
{
	if (node == NULL) 
	{
		return(newNode(key, idx)); 
	}
	if (key < node->key) 
	{
		node->left  = insert(node->left, key, idx); 
	} else if (key > node->key) 
	{
		node->right = insert(node->right, key, idx); 
	} else // Equal keys
	{
		node->idx = idx;
		return node;
	}

	node->height = 1 + MAX(height(node->left), height(node->right)); 

	int balance = getBalance(node); 

	/*
	 * Handle unbalanced case
	 */ 
	// 1. LL
	if (balance > 1 && key < node->left->key) 
	{
		return rightRotate(node); 
	}
	// 2. RR
	if (balance < -1 && key > node->right->key) 
	{
		return leftRotate(node); 
	}
	// 3. LR
	if (balance > 1 && key > node->left->key) 
	{ 
		node->left =  leftRotate(node->left); 
		return rightRotate(node); 
	} 
	// 4. RL
	if (balance < -1 && key < node->right->key) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	return node; 
} 

void findInorderSuccessorPredecessor(NODE *root, int target, int *inSuccessorIdx, int *inPredecessorIdx)
{
	if (root == NULL)
	{
		return;
	}

	if (root->key < target)
	{
		*inPredecessorIdx = root->idx; 
		return findInorderSuccessorPredecessor(root->right, target, inSuccessorIdx, inPredecessorIdx);
	} else if (root->key > target)
	{
		*inSuccessorIdx = root->idx;
		return findInorderSuccessorPredecessor(root->left, target, inSuccessorIdx, inPredecessorIdx);
	} else
	{
		*inPredecessorIdx = root->idx;
		*inSuccessorIdx = root->idx;
		return;
	}
}

int oddEvenJumps(int* A, int ASize)
{
	if (ASize == 1)
	{
		return 1;
	}

	int *dp_odd = calloc(ASize, sizeof(int));
	int *dp_even = calloc(ASize, sizeof(int));

	dp_odd[ASize-1] = dp_even[ASize-1] = 1;    
	NODE *root = NULL;
	root = insert(root, A[ASize-1], ASize-1);    
	for (int i = ASize-2; i >= 0; i--)
	{
		int inorderSuccessor = -1;
		int inorderPredecessor = -1;
		// Find inorder successor and inorder predecessor: O(logn)
		findInorderSuccessorPredecessor(root, A[i], &inorderSuccessor, &inorderPredecessor);
		// calculate dp_odd        
		dp_odd[i] = (inorderSuccessor == -1 ? -1 : dp_even[inorderSuccessor]);
		// calculate dp_even
		dp_even[i] = (inorderPredecessor == -1 ? -1 : dp_odd[inorderPredecessor]);
		// Insert node to AVL tree                
		root = insert(root, A[i], i);
	}

	int ret = 0;
	for (int x = 0; x < ASize; x++)
	{
		if (dp_odd[x] == 1)
		{
			ret++;
		}
	}
	return ret;
}

