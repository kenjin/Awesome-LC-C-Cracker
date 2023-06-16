/**

380. Insert Delete GetRandom O(1) [M]
Ref: https://leetcode.com/problems/insert-delete-getrandom-o1/

Design a data structure that supports all following operations in average O(1) time.

insert(val): Inserts an item val to the set if not already present.
remove(val): Removes an item val from the set if present.
getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.
Example:

// Init an empty set.
RandomizedSet randomSet = new RandomizedSet();

// Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomSet.insert(1);

// Returns false as 2 does not exist in the set.
randomSet.remove(2);

// Inserts 2 to the set, returns true. Set now contains [1,2].
randomSet.insert(2);

// getRandom should return either 1 or 2 randomly.
randomSet.getRandom();

// Removes 1 from the set, returns true. Set now contains [2].
randomSet.remove(1);

// 2 was already in the set, so return false.
randomSet.insert(2);

// Since 2 is the only number in the set, getRandom always return 2.
randomSet.getRandom();

 */

typedef struct nodeInfo NODE;
struct nodeInfo
{
	int key;
	int idx;
	NODE *next;
};

typedef struct 
{
	/* Hash table for insert/delete */
	int hashMod;
	NODE **bucket;
	/* Array for random access*/
	int *arr;
	int arrSize;
	int arrTail;
} RandomizedSet;


NODE* createNode()
{
	NODE *newOne = malloc(sizeof(NODE));
	newOne->idx = -1;
	newOne->next = NULL;
	return newOne;
}

#define HASH_TABE_SIZE (30000)
#define MALLOC_UNIT (500)
RandomizedSet* randomizedSetCreate() 
{
	RandomizedSet* obj = malloc(sizeof(RandomizedSet));
	obj->hashMod = HASH_TABE_SIZE;
	obj->bucket = malloc(sizeof(NODE *)*HASH_TABE_SIZE);
	for (int i = 0; i < HASH_TABE_SIZE; i++)
	{
		obj->bucket[i] = createNode();
	}
	obj->arr = calloc(MALLOC_UNIT, sizeof(int));
	obj->arrSize = MALLOC_UNIT;
	obj->arrTail = -1;

	srand(time(NULL));
	return obj;
}

/* Assmue the val must exist */
void updateHashNodeIdx(RandomizedSet *obj, int val, int newIdx)
{
	int tmpVal = (val < 0 ? (val+INT_MAX) : val); /* negative val case */
	int hashIdx = tmpVal % obj->hashMod;

	NODE *tmp = obj->bucket[hashIdx];
	while (tmp->idx != -1)
	{
		if (tmp->key == val)
		{
			tmp->idx = newIdx;
			return;
		}
		tmp = tmp->next;
	}
}

bool findHash(RandomizedSet *obj, int val)
{
	int tmpVal = (val < 0 ? (val+INT_MAX) : val); /* negative val case */
	int hashIdx = tmpVal % obj->hashMod;

	NODE *tmp = obj->bucket[hashIdx];
	while (tmp->idx != -1)
	{
		if (tmp->key == val)
		{
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
bool randomizedSetInsert(RandomizedSet* obj, int val) 
{
	/* Already in the set */
	if (findHash(obj, val))
	{
		return false;
	}
	/* Update array at first, so we can get position idx */
	obj->arrTail += 1;
	/* dynamic allocation */
	if ((obj->arrTail+1) == obj->arrSize)
	{
		obj->arrSize += MALLOC_UNIT;
		obj->arr = realloc(obj->arr, sizeof(int)*obj->arrSize);
	}
	obj->arr[obj->arrTail] = val;

	/* Update Hash */
	int tmpVal = (val < 0 ? (val+INT_MAX) : val); /* negative val case */
	int hashIdx = tmpVal % obj->hashMod;
	NODE *newNode = createNode();
	/* First bucket set is empty */
	if (obj->bucket[hashIdx]->idx == -1)
	{
		obj->bucket[hashIdx]->key = val;
		obj->bucket[hashIdx]->idx = obj->arrTail; /* record the position in array */
		obj->bucket[hashIdx]->next = newNode;
	} else
	{
		NODE *tmp = obj->bucket[hashIdx];
		while (tmp->idx != -1)
		{
			tmp = tmp->next;
		}
		tmp->key = val;
		tmp->idx = obj->arrTail;
		tmp->next = newNode;
	}

	return true;
}

/** Removes a value from the set. Returns true if the set contained the specified element. */
bool randomizedSetRemove(RandomizedSet* obj, int val) 
{
	/* Already in the set */
	if (!findHash(obj, val))
	{
		return false;
	}
	int tmpVal = (val < 0 ? (val+INT_MAX) : val); /* negative val case */
	int hashIdx = tmpVal % obj->hashMod;

	int arrPos;
	/* Remove the val from the first of bucket*/
	if (obj->bucket[hashIdx]->key == val)
	{
		arrPos = obj->bucket[hashIdx]->idx;
		NODE *tmp = obj->bucket[hashIdx]->next;
		free(obj->bucket[hashIdx]);
		obj->bucket[hashIdx] = tmp;
	} else
	{
		NODE *pre = NULL;
		NODE *tmp = obj->bucket[hashIdx];
		while (tmp->key != val)
		{
			pre = tmp;
			tmp = tmp->next;
		}
		pre->next = tmp->next;
		arrPos = tmp->idx;
		free(tmp);
	}

	/* Remove from array*/
	/* Swap the deleted element and tail element*/
	if (obj->arrTail != arrPos)
	{
		int tmpNum = obj->arr[obj->arrTail];
		obj->arr[obj->arrTail] = obj->arr[arrPos];
		obj->arr[arrPos] = tmpNum;
		/* Update the hash idx of tail element*/
		updateHashNodeIdx(obj, tmpNum, arrPos);
		obj->arrTail -= 1;
	} else
	{
		obj->arrTail -= 1;
	}

	return true;
}

/** Get a random element from the set. */
int randomizedSetGetRandom(RandomizedSet* obj) 
{
	int r = rand() % (obj->arrTail+1);
	return obj->arr[r];
}

void randomizedSetFree(RandomizedSet* obj) 
{
	for (int i = 0; i < HASH_TABE_SIZE; i++)
	{
		NODE *tmpDel = obj->bucket[i];
		if (tmpDel)
		{
			NODE *tmp = tmpDel->next;
			free(tmpDel);
			tmpDel = tmp;
		}
	}
	free(obj->bucket);
	free(obj->arr);
	free(obj);    
}

/**
 * Your RandomizedSet struct will be instantiated and called as such:
 * RandomizedSet* obj = randomizedSetCreate();
 * bool param_1 = randomizedSetInsert(obj, val);

 * bool param_2 = randomizedSetRemove(obj, val);

 * int param_3 = randomizedSetGetRandom(obj);

 * randomizedSetFree(obj);
 */
