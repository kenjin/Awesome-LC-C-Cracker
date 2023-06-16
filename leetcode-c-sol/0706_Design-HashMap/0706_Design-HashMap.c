/**

  706. Design HashMap [E]

  Design a HashMap without using any built-in hash table libraries.

  To be specific, your design should include these functions:

  put(key, value) : Insert a (key, value) pair into the HashMap. If the value already exists in the HashMap, update the value.
  get(key): Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
  remove(key) : Remove the mapping for the value key if this map contains the mapping for the key.

Example:

MyHashMap hashMap = new MyHashMap();
hashMap.put(1, 1);          
hashMap.put(2, 2);         
hashMap.get(1);            // returns 1
hashMap.get(3);            // returns -1 (not found)
hashMap.put(2, 1);          // update the existing value
hashMap.get(2);            // returns 1 
hashMap.remove(2);          // remove the mapping for 2
hashMap.get(2);            // returns -1 (not found) 

Note:

All keys and values will be in the range of [0, 1000000].
The number of operations will be in the range of [1, 10000].
Please do not use the built-in HashMap library.

 */

#define HASH_SIZE 10000
#define HASH_MOD  10000

typedef struct nodeInfo	 NODE;
struct nodeInfo 
{
	int key;
	int val;
	struct nodeInfo *next;
};

typedef struct {
	NODE *bucket[HASH_SIZE]
} MyHashMap;

/** Initialize your data structure here. */

NODE* createNewNode()
{
	NODE *newNode = calloc(1, sizeof(NODE));
	newNode->key = -1;
	newNode->next = NULL;	
	return newNode;
}

MyHashMap* myHashMapCreate() 
{
	MyHashMap *hash = malloc(sizeof(MyHashMap));
	for (int i = 0; i < HASH_SIZE; i++)
	{
		/* Pre-create one node for each bucket */
		hash->bucket[i] = createNewNode();
	}	
	return hash;
}

/** value will always be non-negative. */
void myHashMapPut(MyHashMap* obj, int key, int value) 
{
	int hashIndex = key % HASH_MOD;
	/* Create node */
	NODE *newNode = createNewNode();

	/* Bucket is empty, first time put */
	if (obj->bucket[hashIndex]->next == NULL)
	{
		obj->bucket[hashIndex]->key = key;
		obj->bucket[hashIndex]->val = value;
		obj->bucket[hashIndex]->next = newNode;
	} else
	/* Bucket is not empty*/
	{        
		NODE *tmp = obj->bucket[hashIndex];
		while (tmp->next != NULL)
		{
			if (tmp->key == key)
			{
				tmp->val = value;
				return;
			} else
			{
				tmp = tmp->next;                
			}
		}
		tmp->key = key;
		tmp->val = value;
		tmp->next = newNode;
	}
}

/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
int myHashMapGet(MyHashMap* obj, int key) 
{
	int hashIndex = key % HASH_MOD;     
	NODE *tmp = obj->bucket[hashIndex];
	while (tmp != NULL)
	{
		if (tmp->key == key)
		{            
			return tmp->val;
		} else
		{
			tmp = tmp->next;                
		}
	}

	return -1;
}

/** Removes the mapping of the specified value key if this map contains a mapping for the key */
void myHashMapRemove(MyHashMap* obj, int key) 
{
	int hashIndex = key % HASH_MOD;

	NODE *tmp = obj->bucket[hashIndex];
	/* Case1: The deleting key is matched to first element of bucket */
	if (obj->bucket[hashIndex]->key == key)
	{
		obj->bucket[hashIndex] = tmp->next;
		free(tmp);
	} else
	/* Case2: Traverse all element of backet (The first element must not match the key!)*/
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

void myHashMapFree(MyHashMap* obj) 
{
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

/**
 * Your MyHashMap struct will be instantiated and called as such:
 * MyHashMap* obj = myHashMapCreate();
 * myHashMapPut(obj, key, value);

 * int param_2 = myHashMapGet(obj, key);

 * myHashMapRemove(obj, key);

 * myHashMapFree(obj);
 */
