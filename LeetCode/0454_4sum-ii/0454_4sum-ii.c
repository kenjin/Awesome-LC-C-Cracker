typedef struct hashList HASH_LIST;

struct hashList
{
	int ctr;
	int val;
	HASH_LIST *next;
};

typedef struct
{
	int size;
	int mod;
	HASH_LIST  **list;
} HASH;

int hash(HASH *obj, int key) 
{
	return abs(key) % obj->mod;
}

HASH_LIST * createHashInfo()
{
	HASH_LIST  *newInfo = calloc(1, sizeof(HASH_LIST ));
	return newInfo;
}

HASH* createHash(int size)
{
	HASH *obj = malloc(sizeof(HASH));
	obj->size = obj->mod = size;    
	obj->list = malloc(sizeof(HASH_LIST *)*(size));
	for (int x = 0; x < size; x++)
	{
		obj->list[x] = createHashInfo();
	}
	return obj;
}

void addHash(HASH *obj, int key) 
{
	int hashIndex = hash(obj, key);

	HASH_LIST *newNode = createHashInfo();
	if (obj->list[hashIndex]->next == NULL) // Bucket is empty, first time put
	{
		obj->list[hashIndex]->ctr = 1;
		obj->list[hashIndex]->val = key;
		obj->list[hashIndex]->next = newNode;
	} else // Bucket is not empty
	{   
		HASH_LIST *tmp = obj->list[hashIndex];
		while (tmp->next != NULL)
		{
			if (tmp->val == key)
			{
				tmp->ctr += 1;
				free(newNode);
				return;
			}
			tmp = tmp->next;
		}
		tmp->ctr = 1;
		tmp->val = key;
		tmp->next = newNode;
	}
}

int findHash(HASH *obj, int target) 
{
	int hashIndex = hash(obj, target);
	HASH_LIST *tmp = obj->list[hashIndex];

	while (tmp->next != NULL)
	{
		if (tmp->val == target)
		{
			return tmp->ctr;
		}
		tmp = tmp->next;                
	}
	return 0;
}

void releaseHash(HASH *obj)
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
	free(obj->list);
	free(obj);
}

int fourSumCount(int* A, int ASize, int* B, int BSize, int* C, int CSize, int* D, int DSize)
{
	int ret = 0, size = ASize;

	HASH *h = createHash(size*size+1);
	for (int i = 0; i < size; i++)
	{        
		for (int j = 0; j < size; j++)
		{
			addHash(h, (C[i] + D[j])*(-1));
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int tmpSum = A[i] + B[j];
			ret += findHash(h, tmpSum);
		}
	}

	releaseHash(h);    
	return ret;
}

