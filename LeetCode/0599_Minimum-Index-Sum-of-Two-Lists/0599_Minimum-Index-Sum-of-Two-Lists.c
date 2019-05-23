/**
599. Minimum Index Sum of Two Lists [E]

Suppose Andy and Doris want to choose a restaurant for dinner, and they both have a list of favorite restaurants represented by strings.

You need to help them find out their common interest with the least list index sum. If there is a choice tie between answers, output all of them with no order requirement. You could assume there always exists an answer.

Example 1:
Input:
	["Shogun", "Tapioca Express", "Burger King", "KFC"]
	["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
Output: 
	["Shogun"]
Explanation: The only restaurant they both like is "Shogun".

Example 2:
Input:
	["Shogun", "Tapioca Express", "Burger King", "KFC"]
	["KFC", "Shogun", "Burger King"]
Output: 
	["Shogun"]
Explanation: The restaurant they both like and have the least index sum is "Shogun" with index sum 1 (0+1).

Note:
The length of both lists will be in the range of [1, 1000].
The length of strings in both lists will be in the range of [1, 30].
The index is starting from 0 to the list length minus 1.
No duplicates in both lists.

 */

#define HASH_SIZE 52
#define HASH_MOD  52

typedef struct node NODE;
struct node
{
	char *str;
	int idx;
	NODE *next;
};

typedef struct {    
	NODE *bucket[HASH_SIZE];
} HASH;


/** Initialize your data structure here. */

NODE* nodeCreate()
{
	NODE *n = calloc(1, sizeof(NODE));
	n->next = NULL;
	n->str = NULL;
	n->idx = -1;

	return n;
}

HASH* hashCreate() 
{
	HASH *obj = malloc(sizeof(HASH)*HASH_SIZE);    
	for (int i = 0; i < HASH_SIZE; i++)
	{
		obj->bucket[i] = nodeCreate();
	}
	return obj;
}

void destroyHash(HASH *obj)
{
	for (int i = 0; i < HASH_SIZE; i++)
	{
		NODE *tmp = obj->bucket[i];        
		while (tmp != NULL)
		{
			NODE *nextOne = tmp->next;
			free(tmp->str);
			free(tmp);
			tmp = nextOne;
		}                
	}
	free(obj);
}

int doHash(char *key)
{
	return ((key[0]+key[1]) % HASH_MOD);
}

int findHash(HASH *obj, char *key)
{
	int kenLen = strlen(key);
	/* calculate hash index */
	int hashIdx = doHash(key);

	NODE *tmp = obj->bucket[hashIdx];
	while (tmp->str != NULL)
	{
		if (strcmp(tmp->str, key) == 0)
		{
			return tmp->idx;
		} else
		{
			tmp = tmp->next;   
		}        
	}

	return (-1);
}

void hashAdd(HASH *obj, char *key, int idx)
{
	int keyLen = strlen(key);
	/* calculate hash index */
	int hashIdx = doHash(key);
	NODE *newNode = nodeCreate();
	NODE *tmp = obj->bucket[hashIdx];  
	/* Empty bucket, add it directly */
	if (obj->bucket[hashIdx]->str == NULL)
	{
		obj->bucket[hashIdx]->str = calloc(keyLen+1, sizeof(char));        
		strcpy(obj->bucket[hashIdx]->str, key); 
		obj->bucket[hashIdx]->idx = idx;
		obj->bucket[hashIdx]->next = newNode; 
		return;
	} else
	{      
		while (tmp->next != NULL)
		{
			//printf("%s: msg=%s(%d) vs tmp=%s(%d)\n",__func__, msg, time, tmp->msg, tmp->time);
			/* Match the previous msg, check the time > 10*/            
			if (strcmp(obj->bucket[hashIdx]->str, key) == 0)
			{
				printf("%s: Already add key %s \n", __func__, key);
				free(newNode); /* free */
				return;
			}            
			tmp =  tmp->next;
		}        
	}

	tmp->str = calloc(keyLen+1, sizeof(char)); 
	strcpy(tmp->str , key);
	tmp->idx = idx;
	tmp->next = newNode;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** findRestaurant(char ** list1, int list1Size, char ** list2, int list2Size, int* returnSize)
{
	HASH *h = hashCreate();

	/* Traverse and add to hash table */
	for (int i = 0; i < list1Size; i++)
	{
		hashAdd(h, list1[i], i);
	}
	// The length of both lists will be in the range of [1, 1000].
	int minRes = 2000;
	// Pre-allocate to recuce extra malloc time when excuting (but waste memory)
	char **ret = calloc(list1Size, sizeof(char *));       
	*returnSize = 0;
	for (int i =0; i < list2Size; i++)
	{
		// No need to check min result because of i is bigger then minRes
		if ( i > minRes)
		{
			break;
		}
		int hashRet = findHash(h, list2[i]);
		if (hashRet == -1)
		{
			continue;
		}
		if ((hashRet + i) < minRes)
		{
			*returnSize = 0;
			ret[*returnSize] = calloc(strlen(list1[hashRet]) + 1, sizeof(char));
			strcpy(ret[*returnSize], list1[hashRet]);
			*returnSize += 1;
			minRes = (hashRet + i);
		} else if ((hashRet + i) == minRes)
		{
			ret[*returnSize] = calloc(strlen(list1[hashRet]) + 1, sizeof(char));
			strcpy(ret[*returnSize], list1[hashRet]);
			*returnSize += 1;
		}
	}
	destroyHash(h);

	return ret;
}
