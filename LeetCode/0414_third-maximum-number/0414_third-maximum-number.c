typedef struct
{
	int *arr;
	int size;
} HEAP;

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

bool isEmptyHeap(HEAP *obj)
{
	return (obj->size == 0 ? true : false);
}

void heapify(HEAP *obj, int cur_idx)
{
	int max_idx = cur_idx;
	int l_idx = cur_idx*2 + 1;
	int r_idx = cur_idx*2 + 2;

	if (l_idx < obj->size && obj->arr[max_idx] < obj->arr[l_idx])
	{
		max_idx = l_idx;
	}
	if (r_idx < obj->size && obj->arr[max_idx] < obj->arr[r_idx])
	{
		max_idx = r_idx;
	}

	// The max is left child or right child
	if (max_idx != cur_idx)
	{
		swap(&(obj->arr[max_idx]), &(obj->arr[cur_idx]));
		heapify(obj, max_idx);
	}
}

int delMaxHeap(HEAP *obj)
{
	int ret = obj->arr[0];
	obj->arr[0] = obj->arr[obj->size-1];    
	obj->size -= 1;
	heapify(obj, 0);    
	return ret;
}

HEAP* createHeap(int *n, int nSize)
{
	HEAP *obj = malloc(sizeof(HEAP));
	obj->arr = malloc(sizeof(int)*nSize);
	memcpy(obj->arr, n, sizeof(int)*nSize);
	obj->size = nSize;

	for (int i = (nSize-1)/2; i >= 0; i--)
	{
		heapify(obj, i);
	}

	return obj;
}

void destroyHeap(HEAP *obj)
{
	free(obj->arr);
	free(obj);
}

int thirdMax(int* nums, int numsSize)
{
	HEAP *h = createHeap(nums, numsSize);

	int ret, pre, tmp, delNums = 1;
	ret = delMaxHeap(h);
	pre = ret;
	while (!isEmptyHeap(h))
	{        
		tmp = delMaxHeap(h);        
		delNums = (tmp == pre ? delNums : delNums+1);
		pre = tmp;
		if (delNums == 3)
		{
			ret = tmp;
			break;
		}
	}

	destroyHeap(h);
	return ret;
}


