typedef struct trieNode 
{
	int num;
	struct trieNode  *child[2];
} Trie;

Trie* trieCreate()
{
	Trie *newNode = calloc(1, sizeof(Trie));
	newNode->num = -1;
	return newNode;
}

void trieInsert(Trie* head, int num) 
{
	// transfer to bit representation
	for (int x = 0; x < 31; x++)
	{
		int idx = (num & (0x1 << (30-x))) > 0 ? 1 : 0;
		if (head->child[idx] == NULL)
		{
			head->child[idx] = trieCreate();
		}

		head = head->child[idx];
	}    

	head->num = num;
}

int trieSearchOpposite(Trie* head, int num) 
{
	// transfer to bit representation
	for (int x = 0; x < 31; x++)
	{        
		int idx = (num & (0x1 << (30-x))) > 0 ? 1 : 0;
		// Find the opposite bit to get the larger XOR result
		head = (head->child[idx^1] != NULL ? head->child[idx^1] : head->child[idx]);     
	}
	return head->num;
}

void trieFree(Trie* head) 
{
	if (head == NULL)
	{
		return;
	}

	for (int i = 0; i < 2; i++)
	{
		trieFree(head->child[i]);
	}
	free(head);
}

int findMaximumXOR(int* nums, int numsSize)
{
	Trie *root = trieCreate();
	char bit[32] = {0};
	int max = 0;

	trieInsert(root, nums[0]);
	for (int i = 1; i < numsSize; i++)
	{
		// Find the opposite bit that start from most significant bit as much as possible
		int ret = trieSearchOpposite(root, nums[i]);
		max = (ret ^ nums[i]) > max ? (ret ^ nums[i]) : max;
		// Insert current number
		trieInsert(root, nums[i]);
	}

	trieFree(root);
	return max;
}


