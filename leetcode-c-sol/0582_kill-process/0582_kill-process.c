#define MALLOC_UNIT     (10000)

typedef struct linked_list
{
	int id;
	struct linked_list *next;
} LIST;

typedef struct
{
	int pid;
	LIST *child_head;
} PROCESS_NODE;

typedef struct
{
	int size;
	int mod;
	PROCESS_NODE *p;
} HASH_MAP;

void addList(LIST *l, int pid)
{
	LIST *tmp = l->next;    
	LIST *nL = malloc(sizeof(LIST));
	l->next = nL;
	nL->id = pid;    
	nL->next = tmp;
}

void freeList(LIST *l)
{    
	while (l)
	{
		LIST *tmp = l;
		l = l->next;
		free(tmp);
	}
}

HASH_MAP* createHash(int size)
{
	HASH_MAP *obj = malloc(sizeof(HASH_MAP)*size);
	obj->size = size;
	obj->mod = size;
	obj->p = calloc(size, sizeof(PROCESS_NODE));
	return obj;
}

void releaseHash(HASH_MAP *h)
{
	for (int x = 0; x < h->size; x++)
	{
		freeList(h->p[x].child_head);
	}
	free(h->p);
	free(h);
}

int hash(HASH_MAP *obj, int key) 
{
	int r = key % obj->mod;
	return r < 0 ? r + obj->size : r;
}

void addHash(HASH_MAP *h, int pid, int cpid)
{
	int hashIdx = hash(h, pid);

	while (h->p[hashIdx].child_head != NULL)
	{
		// pid has already existed
		if (h->p[hashIdx].pid == pid)
		{
			addList(h->p[hashIdx].child_head, cpid);
			return;
		}
		hashIdx = (hashIdx+1) % h->size;        
	}
	h->p[hashIdx].pid = pid;    
	h->p[hashIdx].child_head = calloc(1, sizeof(LIST));
	addList(h->p[hashIdx].child_head, cpid);
}

LIST* findHash(HASH_MAP *h, int pid)
{
	int hashIdx = hash(h, pid);
	while (h->p[hashIdx].child_head != NULL)
	{
		if (h->p[hashIdx].pid == pid)
		{
			return h->p[hashIdx].child_head->next;
		}
		hashIdx = (hashIdx+1) % h->size;        
	}

	return NULL;
}

void killProcessHelper(HASH_MAP *h, int kill, int **ret, int *retSize)
{
	if ((*retSize + 1) % MALLOC_UNIT == 0)
	{
		*ret = realloc(*ret, sizeof(int)*(*retSize + MALLOC_UNIT));
	}    
	(*ret)[*retSize] = kill;
	*retSize += 1;

	LIST *cpids = findHash(h, kill);
	if (NULL == cpids)
	{
		return;
	}

	while (cpids)
	{
		killProcessHelper(h, cpids->id, ret, retSize);
		cpids = cpids->next;
	}
}

int* killProcess(int* pid, int pidSize, int* ppid, int ppidSize, int kill, int* returnSize)
{
	HASH_MAP *h = createHash(pidSize+1);

	for (int i = 0; i < pidSize; i++)
	{
		addHash(h, ppid[i], pid[i]);
	}

	int *ret = malloc(sizeof(int)*MALLOC_UNIT);
	*returnSize = 0;
	killProcessHelper(h, kill, &ret, returnSize);

	releaseHash(h);
	return ret;
}


