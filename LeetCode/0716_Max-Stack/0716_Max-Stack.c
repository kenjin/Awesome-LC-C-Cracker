#define MAX_STACK_SIZE 10000
typedef struct
{
	int oriStack[MAX_STACK_SIZE];
	int maxStack[MAX_STACK_SIZE];    
	int oriSize;
	int maxSize;
} MaxStack;


MaxStack* maxStackCreate() 
{
	MaxStack *obj = malloc(sizeof(MaxStack));
	obj->oriSize = 0;
	obj->maxSize = 0;
	return obj;
}

void maxStackPush(MaxStack* obj, int x) 
{        
	obj->oriStack[obj->oriSize] = x;
	if (obj->maxSize == 0 || x >= obj->maxStack[obj->maxSize-1])
	{
		obj->maxStack[obj->maxSize] = x;        
	} else 
	{
		obj->maxStack[obj->maxSize] = obj->maxStack[obj->maxSize-1];        
	}
	obj->maxSize ++;
	obj->oriSize ++;
}

int maxStackPop(MaxStack* obj) 
{    
	int ret = obj->oriStack[obj->oriSize-1];
	obj->oriSize --;
	obj->maxSize --;
	return ret;
}

int maxStackTop(MaxStack* obj) 
{    
	return obj->oriStack[obj->oriSize-1];  
}

int maxStackPeekMax(MaxStack* obj) 
{
	return obj->maxStack[obj->maxSize-1];
}

int maxStackPopMax(MaxStack* obj) 
{   
	int max = obj->maxStack[obj->maxSize-1];
	int tmpSize = 0;
	int *tmpStack = malloc(sizeof(int)*obj->oriSize);

	while (1)
	{
		if (maxStackTop(obj) != max)
		{
			tmpStack[tmpSize] = maxStackTop(obj);
			maxStackPop(obj);
			tmpSize++;
		} else
		{
			maxStackPop(obj);
			break;
		}        
	}    

	while (tmpSize > 0)
	{                
		maxStackPush(obj, tmpStack[tmpSize-1]);
		tmpSize--;
	}

	free(tmpStack);
	return max;
}

void maxStackFree(MaxStack* obj) 
{
	free(obj);    
}

/**
 * Your MaxStack struct will be instantiated and called as such:
 * MaxStack* obj = maxStackCreate();
 * maxStackPush(obj, x);

 * int param_2 = maxStackPop(obj);

 * int param_3 = maxStackTop(obj);

 * int param_4 = maxStackPeekMax(obj);

 * int param_5 = maxStackPopMax(obj);

 * maxStackFree(obj);
 */
