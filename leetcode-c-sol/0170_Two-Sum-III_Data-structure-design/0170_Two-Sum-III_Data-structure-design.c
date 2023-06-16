/**
170. Two Sum III - Data structure design [E]
Ref: https://leetcode.com/problems/two-sum-iii-data-structure-design/

Design and implement a TwoSum class. It should support the following operations: add and find.

add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

Example 1:
add(1); add(3); add(5);
find(4) -> true
find(7) -> false

 */

#define HASH_SIZE           10000
#define MALLOC_SIZE_UNIT    1000

typedef struct nodeInfo NODE;
struct nodeInfo
{
	int ctr;
	int val;
	struct nodeInfo *next;
};

typedef struct
{
	int arrSize;
	int *arr;
	int mod;
	NODE *bucket[HASH_SIZE]
} TwoSum;

NODE* createNewNode()
{
	NODE *newNode = calloc(1, sizeof(NODE));
	newNode->ctr = 0;
	newNode->val = 0;
	newNode->next = NULL;
	return newNode;
}

TwoSum* twoSumCreate()
{
	TwoSum *obj = malloc(sizeof(TwoSum));
	obj->mod = HASH_SIZE;
	obj->arrSize = 0;
	obj->arr = malloc(sizeof(int)*MALLOC_SIZE_UNIT);
	for (int i = 0; i < HASH_SIZE; i++)
	{
		/* Pre-create one node for each bucket */
		obj->bucket[i] = createNewNode();
	}
	return obj;
}

void twoSumFree(TwoSum* obj)
{
	free(obj->arr);
	for (int i = 0; i < HASH_SIZE; i++)
	{
		NODE *tmp = obj->bucket[i];
		while (tmp)
		{
			NODE *delNode = tmp;
			tmp = tmp->next;
			free(delNode);
		}
	}
	free(obj);
}

/** value will always be non-negative. */
void twoSumAdd(TwoSum* obj, int number)
{
	int tmpNum = number;
	if (tmpNum < 0)
	{
		tmpNum += INT_MAX;
	}
	int hashIndex = tmpNum % obj->mod;
	/* Create node */
	NODE *newNode = createNewNode();

	/* Bucket is empty, first time put */
	if (obj->bucket[hashIndex]->next == NULL)
	{
		obj->bucket[hashIndex]->val = number;
		obj->bucket[hashIndex]->ctr = 1;
		obj->bucket[hashIndex]->next = newNode;
	} else
		/* Bucket is not empty*/
	{
		NODE *tmp = obj->bucket[hashIndex];
		while (tmp->next != NULL)
		{
			if (tmp->val == number)
			{
				/* duplicate number */
				//printf("duplicate:%d!!\n", number);
				tmp->ctr += 1;
				free(newNode);
				return;
			}
			tmp = tmp->next;
		}
		tmp->val = number;
		tmp->ctr = 1;
		tmp->next = newNode;
	}
	/* Add to array */
	obj->arrSize += 1;
	if (obj->arrSize % MALLOC_SIZE_UNIT == 0)
	{
		obj->arr = realloc(obj->arr, sizeof(int)*(obj->arrSize+MALLOC_SIZE_UNIT));
	}
	obj->arr[obj->arrSize-1] = number;
}

int findHash(TwoSum* obj, int number)
{
	int tmpNum = number;
	if (tmpNum < 0)
	{
		tmpNum += INT_MAX;
	}
	int hashIndex = tmpNum % obj->mod;
	NODE *tmp = obj->bucket[hashIndex];
	while (tmp != NULL)
	{
		if (tmp->val == number)
		{
			return tmp->ctr;
		}
		tmp = tmp->next;
	}
	return -1;
}

bool twoSumFind(TwoSum* obj, int value)
{
	for (int x = 0; x < obj->arrSize; x++)
	{
		int findNum = value - obj->arr[x];
		int result = findHash(obj, findNum);

		if ((findNum == obj->arr[x] && result > 1) ||
				(findNum != obj->arr[x] && result > 0))
		{
			return true;
		}
	}
	return false;
}
/**
 * Your TwoSum struct will be instantiated and called as such:
 * TwoSum* obj = twoSumCreate();
 * twoSumAdd(obj, number);

 * bool param_2 = twoSumFind(obj, value);

 * twoSumFree(obj);
 */
