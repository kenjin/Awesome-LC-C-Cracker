/**

350. Intersection of Two Arrays II [E]
Ref: https://leetcode.com/problems/intersection-of-two-arrays-ii/

 */

typedef struct nodeInfo NODE;
struct nodeInfo
{
	int key;
	int ctr;
	NODE *next;
};

typedef struct hash
{
	int bucketSize;
	int mod;
	NODE **bucket;
} HASH;

NODE* createNode()
{
	NODE *newNode = calloc(1, sizeof(NODE));
	newNode->next = NULL;
	return newNode;
}

HASH* createHash(int size)
{
	HASH *obj = malloc(sizeof(HASH));
	obj->bucketSize = size;
	obj->mod = size;
	obj->bucket = malloc(sizeof(NODE*)*size);
	for (int i = 0; i < size; i++)
	{
		obj->bucket[i] = createNode();
	}        
	return obj;
}

void destroyHash(HASH *obj)
{
	for (int i = 0; i < obj->bucketSize; i++)
	{
		NODE *delNode = obj->bucket[i];
		while (delNode != NULL)
		{
			NODE *tmpDel = delNode->next;            
			free(delNode);
			delNode = tmpDel;
		}
	}
	free(obj);
}

int dohash(int key, int mod)
{
	if (key < 0)
	{
		key = (key+1)*(-1);
	}
	return (key % mod);
}

bool findHash(HASH *obj, int key)
{
	int hashIdx = dohash(key, obj->mod);
	NODE *tmp = obj->bucket[hashIdx];
	while (tmp != NULL)
	{
		if (tmp->key == key && tmp->ctr != 0)
		{
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

void addHash(HASH *obj, int key)
{
	int hashIdx = dohash(key, obj->mod);

	if (obj->bucket[hashIdx]->ctr == 0)
	{
		obj->bucket[hashIdx]->key = key;
		obj->bucket[hashIdx]->ctr = 1;
		NODE *nextOne = createNode();
		obj->bucket[hashIdx]->next = nextOne;
		//printf("%s: Add first node %d(ctr=%d) \n", __func__, obj->bucket[hashIdx]->key, obj->bucket[hashIdx]->ctr);
	} else
	{
		NODE *tmp = obj->bucket[hashIdx];
		while (tmp->ctr != 0)
		{
			if (tmp->key == key)
			{
				tmp->ctr++;
				//printf("%s: Duplicate %d, update ctr %d\n", __func__, tmp->key, tmp->ctr);
				return;
			}
			tmp = tmp->next;
		}
		NODE *nextOne = createNode();
		tmp->key = key;
		tmp->ctr = 1;
		tmp->next = nextOne;
		//printf("%s: Add node %d(ctr=%d) \n", __func__, tmp->key, tmp->ctr);
	}
}

void delHash(HASH *obj, int key)
{
	int hashIdx = dohash(key, obj->mod);

	if (!findHash(obj,key))
	{
		//printf("%s: WARNING not found!\n", __func__);
		return;
	}

	/* Match at the first node of bucket */
	if (obj->bucket[hashIdx]->key == key)
	{
		obj->bucket[hashIdx]->ctr -= 1;
		//printf("%s: remove first node %d(ctr=%d) \n", __func__, obj->bucket[hashIdx]->key, obj->bucket[hashIdx]->ctr);
		if (obj->bucket[hashIdx]->ctr == 0)
		{            
			NODE *tmp = obj->bucket[hashIdx];
			obj->bucket[hashIdx] = obj->bucket[hashIdx]->next;
			free(tmp);
		}
	} else
	{
		NODE *tmp = obj->bucket[hashIdx];
		while (tmp->next != NULL)
		{
			if (tmp->next->key == key)
			{
				tmp->next->ctr -= 1;
				//printf("%s: Delete node %d(ctr=%d) \n", __func__, tmp->next->key, tmp->next->ctr);
				if (tmp->next->ctr == 0)
				{
					NODE *tmpDel = tmp->next->next;
					free(tmp->next);
					tmp->next = tmpDel;            
				}
				break;  
			}
			tmp = tmp->next;
		}        
	}
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize)
{
	int len1 = strlen(nums1);
	int len2 = strlen(nums2);

	int bigSize = nums1Size > nums2Size ? nums1Size : nums2Size;    
	HASH *hash = createHash(bigSize);

	int *ret = malloc(sizeof(int));
	*returnSize = 0;

	for (int i = 0; i < nums1Size; i++)
	{
		addHash(hash, nums1[i]);
	}

	for (int i = 0; i < nums2Size; i++)
	{
		if (findHash(hash, nums2[i]))
		{
			delHash(hash, nums2[i]);
			//printf("Find Intersection: %d\n", nums2[i]);
			*returnSize += 1;
			ret = realloc(ret, sizeof(int)*(*returnSize));
			ret[(*returnSize)-1] = nums2[i];            
		}
	}

	destroyHash(hash);
	return ret;
}
