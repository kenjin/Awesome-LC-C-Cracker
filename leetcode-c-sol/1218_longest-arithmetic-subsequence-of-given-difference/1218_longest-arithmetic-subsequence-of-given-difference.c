#define MAX(a, b)   (a > b ? a : b)

typedef struct linked_list
{
	struct linked_list *next;
	int val;
	int idx;
}LL;

typedef struct 
{
	int max;
	int size;
	LL **list;
	int *dp;
}LAS_DIFF; // Longest Arithmetic Subsequence of Given Difference

int hash(LAS_DIFF *obj, int target)
{
	if (target < 0)
	{
		target *= -1;
	}
	return target % obj->size;
}

LAS_DIFF* createObj(int size)
{
	LAS_DIFF *obj = malloc(sizeof(LAS_DIFF));
	obj->max = 1;
	obj->size = size;    
	obj->list = malloc(sizeof(LL *)*(size));    
	for (int x = 0; x < size; x++)
	{
		obj->list[x] = calloc(1, sizeof(LL));
	}
	obj->dp = malloc(sizeof(int)*size);

	return obj;
}

void addElement(LAS_DIFF *obj, int key, int idx) 
{
	int hashIdx = hash(obj, key);
	LL *tmp = obj->list[hashIdx];
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->idx = idx;
	tmp->val = key;
	tmp->next = calloc(1, sizeof(LL));
}

void updateDP(LAS_DIFF *obj, int target, int targetIdx) 
{
	int hashIdx = hash(obj, target);
	LL *tmp = obj->list[hashIdx];
	int tmpMax = 1;
	while (tmp->next != NULL)
	{
		if (tmp->val == target)
		{
			tmpMax = MAX(obj->dp[tmp->idx] + 1, tmpMax);
		}
		tmp = tmp->next;
	}
	obj->dp[targetIdx] = tmpMax;    
	obj->max = MAX(obj->max, tmpMax);
}

void releaseObj(LAS_DIFF *obj)
{
	for (int i = 0; i < obj->size; i++)
	{
		LL *delNode = obj->list[i];
		while (delNode)
		{
			LL *tmp = delNode->next;
			free(delNode);
			delNode = tmp;
		}
	}
	free(obj->list);
	free(obj->dp);
	free(obj);
}

int longestSubsequence(int* arr, int arrSize, int difference)
{    
	LAS_DIFF *obj = createObj(arrSize);

	for (int i = 0; i < arrSize; i++)
	{        
		int target = arr[i] - difference;
		updateDP(obj, target, i);
		addElement(obj, arr[i], i);
	}

	int ret = obj->max;
	releaseObj(obj);
	return ret;
}


