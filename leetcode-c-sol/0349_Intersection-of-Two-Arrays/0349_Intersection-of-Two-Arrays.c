/**

349. Intersection of Two Arrays [E]
Ref: https://leetcode.com/problems/intersection-of-two-arrays/

Given two arrays, write a function to compute their intersection.

Example 1:
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]

Example 2:
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]

Note:
Each element in the result must be unique.
The result can be in any order.

 */

typedef struct nodeInfo	 NODE;
struct nodeInfo 
{
	int key;
	int set;
	struct nodeInfo *next;
};

typedef struct {
	NODE **bucket;
} MyHashMap;

/*
 * Initialize your data structure here. 
 */
NODE* createNewNode()
{
	NODE *newNode = calloc(1, sizeof(NODE));
	newNode->next = NULL;	
	return newNode;
}

MyHashMap* myHashMapCreate(int size) 
{
	MyHashMap *hash = malloc(sizeof(MyHashMap));
	hash->bucket = malloc(sizeof(NODE *)*size);
	for (int i = 0; i < size; i++)
	{
		/* Pre-create one node for each bucket */
		hash->bucket[i] = createNewNode();
	}	
	return hash;
}

/*
 * value will always be non-negative. 
 */
void myHashMapPut(MyHashMap* obj, int key, int mod) 
{
	int hashIndex = key % mod;

	/* Create node */
	NODE *newNode = createNewNode();

	/* Bucket is empty, first time put */
	if (obj->bucket[hashIndex]->next == NULL)
	{
		obj->bucket[hashIndex]->key = key;
		obj->bucket[hashIndex]->set = 1;
		obj->bucket[hashIndex]->next = newNode;
	} else
		/* Bucket is not empty*/
	{        
		NODE *tmp = obj->bucket[hashIndex];
		while (tmp->next != NULL)
		{
			if (tmp->key == key)
			{
				//printf("Duplicate key=%d\n", key);
				return;
			} else
			{
				tmp = tmp->next;                
			}
		}
		tmp->key = key;
		tmp->set = 1;
		tmp->next = newNode;
	}
}

/*
 * Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key 
 */
bool myHashMapGet(MyHashMap* obj, int key, int mod) 
{
	int hashIndex = key % mod;     
	NODE *tmp = obj->bucket[hashIndex];
	while (tmp != NULL)
	{
		if (tmp->set && tmp->key == key)
		{            
			//printf("Find key=%d\n", key);
			return true;
		} else
		{
			tmp = tmp->next;                
		}
	}

	return false;
}

/*
 * Removes the mapping of the specified value key if this map contains a mapping for the key 
 */
void myHashMapRemove(MyHashMap* obj, int key, int mod) 
{
	int hashIndex = key % mod;

	NODE *tmp = obj->bucket[hashIndex];
	/* Case1: The deleting key is matched to first element of bucket */
	if (obj->bucket[hashIndex]->key == key)
	{
		obj->bucket[hashIndex] = tmp->next;
		free(tmp);
	} else
	/* Case2: Traverse all element of backet (The first element must not match the key!) */
	{    
		NODE *prevNode = NULL;        
		while (tmp)
		{
			if (tmp->key == key)
			{
				prevNode->next = tmp->next;
				free(tmp);
				break;
			} else
			{            
				prevNode = tmp;
				tmp = tmp->next;
			}
		}
	}
}

void myHashMapFree(MyHashMap* obj, int size) 
{
	for (int i = 0; i < size; i++)
	{
		NODE *tmp = obj->bucket[i];
		while (tmp)
		{
			NODE *delNode = tmp;
			tmp = tmp->next;
			free(delNode);
		}   
	}
	free(obj->bucket);
	free(obj);
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize)
{
	int bigSize   = (nums1Size > nums2Size ? nums1Size : nums2Size);

	int mod = bigSize;
	MyHashMap *hash = myHashMapCreate(bigSize);
	int *ret = malloc(sizeof(int));
	*returnSize = 0;

	for (int x = 0; x < nums1Size; x++)
	{
		myHashMapPut(hash, nums1[x], mod);
	}  
	for (int x = 0; x < nums2Size; x++)
	{
		if (myHashMapGet(hash, nums2[x], mod) == true)
		{
			*returnSize += 1;
			ret = realloc(ret, sizeof(int)*(*returnSize));
			ret[(*returnSize)-1] = nums2[x]; 

			myHashMapRemove(hash, nums2[x], mod);
		}
	}    

	myHashMapFree(hash, bigSize);
	return ret;
}


