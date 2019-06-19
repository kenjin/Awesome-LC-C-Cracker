typedef struct hashList HASH_LIST;
typedef struct linkedList LINKED_LIST;
typedef struct hashTable HASH;

struct linkedList
{
	int key;
	int val;
	LINKED_LIST *prev;
	LINKED_LIST *next;
};

// Use linked list to solve hash conflict
struct hashList 
{
	int key;
	int val;
	LINKED_LIST *ptr;
	HASH_LIST *next;
};

struct hashTable
{
	int size;
	int mod;
	HASH_LIST **list;
};

typedef struct 
{
	int curCapacity;
	int capacity;
	LINKED_LIST *head;
	HASH *hash;
} LRUCache;

LINKED_LIST* linkedListCreate(int key, int val) 
{
	LINKED_LIST *newNode = calloc(1, sizeof(LINKED_LIST));
	newNode->next = newNode->prev = NULL;
	newNode->key = key;
	newNode->val = val;
	return newNode;
}

LINKED_LIST* initList()
{
	LINKED_LIST *head = linkedListCreate(-1, -1);
	head->prev = head;
	head->next = head;
	return head;
}

void _addList(LINKED_LIST *new, LINKED_LIST *prev, LINKED_LIST *next)
{
	prev->next = new;
	new->prev = prev;
	new->next = next;
	next->prev = new;
}

LINKED_LIST* addListFront(LINKED_LIST *head, int key, int val)
{
	LINKED_LIST *new = linkedListCreate(key, val);
	_addList(new, head, head->next);
	return new;
}

void removeListNode(LINKED_LIST *head, LINKED_LIST *target)
{
	LINKED_LIST *prevTarget = target->prev;
	LINKED_LIST *nextTarget = target->next;

	prevTarget->next = nextTarget;
	nextTarget->prev = prevTarget;
	free(target);
}

// return key for hash delete
int removeListRear(LINKED_LIST *head)
{
	LINKED_LIST *rear = head->prev;    
	int ret = rear->key;
	removeListNode(head, rear);
	return ret;
}

void freeList(LINKED_LIST *head)
{
	LINKED_LIST *tmp = head->next;
	while (tmp != head)
	{
		LINKED_LIST *delList = tmp->next;
		free(tmp);
		tmp = delList;
	}
	free(head);
}

HASH_LIST* createNewNode()
{
	HASH_LIST *newNode = calloc(1, sizeof(HASH_LIST));
	newNode->key = -1;
	newNode->next = NULL;	
	return newNode;
}

HASH* hashCreate(int size) 
{
	HASH *hash = malloc(sizeof(HASH));
	hash->size = hash->mod = size;
	hash->list = malloc(sizeof(HASH_LIST*)*size);
	for (int i = 0; i < size; i++)
	{
		/* Pre-create one node for each bucket */
		hash->list[i] = createNewNode();
	}	
	return hash;
}

/** value will always be non-negative. */
void hashPut(HASH* obj, int key, int value, LINKED_LIST *ptr)
{
	int hashIndex = key % obj->mod;
	/* Create node */
	HASH_LIST *newNode = createNewNode();

	if (obj->list[hashIndex]->next == NULL) /* Bucket is empty, first time put */
	{
		obj->list[hashIndex]->key = key;
		obj->list[hashIndex]->val = value;
		obj->list[hashIndex]->ptr = ptr;
		obj->list[hashIndex]->next = newNode;
	} else /* Bucket is not empty*/
	{
		HASH_LIST *tmp = obj->list[hashIndex];
		while (tmp->next != NULL)
		{
			// update value and ptr
			if (tmp->key == key)
			{
				tmp->val = value;
				tmp->ptr = ptr;
				free(newNode);
				return;
			}
			tmp = tmp->next;
		}
		tmp->key = key;
		tmp->val = value;
		tmp->ptr = ptr;
		tmp->next = newNode;
	}
}

void hashPop(HASH* obj, int key) 
{
	int hashIndex = key % obj->mod;     
	HASH_LIST *tmp = obj->list[hashIndex];
	if (tmp->key == key)
	{
		obj->list[hashIndex] = tmp->next;
		free(tmp);
		return;
	}

	HASH_LIST *prevList = NULL;
	while (tmp->next != NULL)
	{
		if (tmp->key == key)
		{
			prevList->next = tmp->next;
			free(tmp);
			return;
		}
		prevList = tmp;
		tmp = tmp->next;                
	}
}

HASH_LIST* hashCheck(HASH* obj, int key) 
{
	int hashIndex = key % obj->mod;     
	HASH_LIST *tmp = obj->list[hashIndex];
	// check first list
	if (tmp->key == key)
	{
		return tmp;
	}
	// check the second to the end, the purpose is to count to the last node
	while (tmp->next != NULL)
	{
		if (tmp->key == key)
		{
			return tmp;
		}
		tmp = tmp->next;                
	}

	return NULL;
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

LRUCache* lRUCacheCreate(int capacity) 
{    
	LRUCache *obj = malloc(sizeof(LRUCache));
	obj->curCapacity = 0;
	obj->capacity = capacity;
	obj->head = initList();
	obj->hash = hashCreate(capacity);

	return obj;
}

void lRUCacheUpdateInput(LRUCache* obj, int key, int value) 
{
	LINKED_LIST* newList = addListFront(obj->head, key, value);
	hashPut(obj->hash, key, value, newList);
}

int lRUCacheGet(LRUCache* obj, int key) 
{
	HASH_LIST *checkInfo = hashCheck(obj->hash, key);
	if (checkInfo != NULL)
	{
		removeListNode(obj->head, checkInfo->ptr);
		lRUCacheUpdateInput(obj, checkInfo->key, checkInfo->val);
		return checkInfo->val;
	} else
	{
		return -1;
	}
}

void lRUCachePut(LRUCache* obj, int key, int value) 
{
	HASH_LIST *checkInfo = hashCheck(obj->hash, key);
	if (checkInfo != NULL) // Update linked list, no need to update hash table
	{
		// remove the original node from linked list
		removeListNode(obj->head, checkInfo->ptr);
	} else // Add new node
	{
		if (obj->curCapacity == obj->capacity)
		{
			// remove the oldest element
			int delKey = removeListRear(obj->head);
			// remove from the hash table
			hashPop(obj->hash, delKey);
		} else
		{
			obj->curCapacity += 1;
		}
	}
	lRUCacheUpdateInput(obj, key, value);
}

void lRUCacheFree(LRUCache* obj)
{
	freeList(obj->head);
	hashFree(obj->hash);
	free(obj);
	return;
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);

 * lRUCachePut(obj, key, value);

 * lRUCacheFree(obj);
 */
