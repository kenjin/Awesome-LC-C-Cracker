typedef struct hashList HASH_LIST;
struct hashList 
{
	int val;
	HASH_LIST *next;
};

typedef struct 
{
	int size;
	int mod;
	HASH_LIST **list;
} HASH;


HASH_LIST* createNewNode(int val)
{
	HASH_LIST *newNode = calloc(1, sizeof(HASH_LIST));
	newNode->val = val;	
	return newNode;
}

HASH* hashCreate(int size) 
{
	HASH *hash = malloc(sizeof(HASH));
	hash->size = hash->mod = size;
	hash->list = calloc(size,sizeof(HASH_LIST*));
	return hash;
}

int doHash(int mod, int val)
{
	return val % mod;
}

void hashInsert(HASH* obj, int val)
{
	int hashIndex = doHash(obj->mod, val);
	HASH_LIST *newNode = createNewNode(val);
	HASH_LIST *tmp = obj->list[hashIndex];
	if (tmp == NULL)
	{
		obj->list[hashIndex] = newNode;
		return;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = newNode;
}

bool hashFind(HASH* obj, int val) 
{
	int hashIndex = doHash(obj->mod, val);
	HASH_LIST *tmp = obj->list[hashIndex];

	while (tmp != NULL)
	{
		if (tmp->val == val)
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


int subarrayBitwiseORs(int* A, int ASize)
{
	HASH *h = hashCreate(ASize+1);

	int set[32] = {0};
	int setCtr = 0, ret = 0;
	for (int i = 0; i < ASize; i++)
	{
		HASH *hTmp = hashCreate(setCtr+1);

		int curSetCtr = setCtr;
		setCtr = 0;
		for (int x = 0; x < curSetCtr; x++)
		{
			int cur = (set[x] | A[i]);

			if (!hashFind(hTmp, cur))
			{
				hashInsert(hTmp, cur);
				set[setCtr] = cur;
				setCtr++;
			}
			if (!hashFind(h, cur))
			{                
				hashInsert(h, cur);
				ret++;
			}            
		}

		if (!hashFind(hTmp, A[i]))
		{
			set[setCtr] = A[i];
			setCtr++;
		}

		if (!hashFind(h, A[i]))
		{        
			hashInsert(h, A[i]);
			ret++;
		}
		hashFree(hTmp);
	}

	hashFree(h);
	return ret;
}


