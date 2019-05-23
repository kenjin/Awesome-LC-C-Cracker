/**
219. Contains Duplicate II [E]

Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the absolute difference between i and j is at most k.

Example 1:
Input: nums = [1,2,3,1], k = 3
Output: true

Example 2:
Input: nums = [1,0,1,1], k = 1
Output: true

Example 3:
Input: nums = [1,2,3,1,2,3], k = 2
Output: false

 */

typedef struct hashList HASH_LIST;
struct hashList 
{
	int key;
	int val;
	HASH_LIST *next;
};

typedef struct 
{
	int size;
	int mod;
	int k;
	HASH_LIST **list
} HASH;

/** Initialize your data structure here. */

HASH_LIST* createNewNode()
{
	HASH_LIST *newNode = calloc(1, sizeof(HASH_LIST));
	newNode->key = -1;
	newNode->next = NULL;	
	return newNode;
}

HASH* hashCreate(int size, int k) 
{
	HASH *hash = malloc(sizeof(HASH));
	hash->size = hash->mod = size;
	hash->k = k;
	hash->list = malloc(sizeof(HASH_LIST*)*size);
	for (int i = 0; i < size; i++)
	{
		/* Pre-create one node for each bucket */
		hash->list[i] = createNewNode();
	}	
	return hash;
}

/** value will always be non-negative. */
void hashPut(HASH* obj, int key, int value) 
{
	int tmpKey = (key < 0 ? (key+1)*(-1) : key);
	int hashIndex = tmpKey % obj->mod;
	/* Create node */
	HASH_LIST *newNode = createNewNode();

	/* Bucket is empty, first time put */
	if (obj->list[hashIndex]->next == NULL)
	{
		if (value == 0)
			printf("Put %d(%d)\n", key, value);
		obj->list[hashIndex]->key = key;
		obj->list[hashIndex]->val = value;
		obj->list[hashIndex]->next = newNode;
	} else
		/* Bucket is not empty*/
	{        
		HASH_LIST *tmp = obj->list[hashIndex];
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		//printf("@@ut %d(%d)\n", key, value);
		tmp->key = key;
		tmp->val = value;
		tmp->next = newNode;
	}
}

bool hashCheck(HASH* obj, int key, int target) 
{
	int tmpKey = (key < 0 ? (key+1)*(-1) : key);
	int hashIndex = tmpKey % obj->mod;     
	HASH_LIST *tmp = obj->list[hashIndex];
	// check first list
	if (tmp->key == key &&
			abs(tmp->val - target) <= obj->k)
	{
		return true;
	}
	// check the second to the end, the purpose is to cound the last node
	// if the input key/target is -1/XX, it will match to the last node (because default key is -1)
	while (tmp->next != NULL)
	{
		if (tmp->key == key &&
				abs(tmp->val - target) <= obj->k)
		{
			return true;
		}
		tmp = tmp->next;                
	}

	return false;
}

void hashFree(HASH* obj) 
{
	for (int i = 0; i < obj->size; i++)
	{
		HASH_LIST *tmp = obj->list[i];
		while (tmp)
		{
			HASH_LIST *delNode = tmp;
			tmp = tmp->next;
			free(delNode);
		}   
	}
	free(obj);
}


bool containsNearbyDuplicate(int* nums, int numsSize, int k)
{
	HASH *hash = hashCreate(3000, k);
	for (int i = 0; i < numsSize; i++)
	{
		if (hashCheck(hash, nums[i], i))
		{
			return true;
		} 
		hashPut(hash, nums[i], i);
	}
	return false;
}

