/**

739. Daily Temperatures [Medium]

Given a list of daily temperatures T, return a list such that, for each day 
in the input, tells you how many days you would have to wait until a warmer 
temperature. If there is no future day for which this is possible, put 0 instead.

For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73], 
your output should be [1, 1, 4, 2, 1, 1, 0, 0].

Note: The length of temperatures will be in the range [1, 30000]. 
      Each temperature will be an integer in the range [30, 100].

*/

struct linkedList
{
	int data;
	int index; /* Store the index of descending head */
	struct linkedList *next;
};
typedef struct linkedList LIST_NODE;

typedef struct
{
	LIST_NODE *head;
} STACK;

/** initialize your data structure here. */
STACK* stackCreate() {
	STACK *obj = malloc(sizeof(STACK));
	obj->head = NULL;
	return obj;
}

void stackPush(STACK* obj, int val, int idx)
{
	/* Push and make the new node be the "head" of STACK*/
	LIST_NODE *node = malloc(sizeof(LIST_NODE));
	node->data = val;
	node->index = idx;
	node->next = NULL;

	/* Update node position and min. */
	/* Case 1: First push */
	if (obj->head == NULL)
	{
		/* NULL => [Node1]->NULL */
		obj->head = node;
	} else
		/* Case 2: Already have node(s) */
	{
		/* [Node1]->NULL => [Node2]->[Node1]->NULL
		 *  ^HEAD            ^New_Head
		 */
		node->next = obj->head;
		obj->head = node;
	}
}

void stackPop(STACK* obj)
{
	if (obj->head == NULL)
	{
		printf("WARNING: empty stack!\n");
		return;
	}

	/* Only one element in stack*/
	if (obj->head->next == NULL)
	{
		free(obj->head);
		obj->head = NULL;
	} else
	{
		LIST_NODE *tmp = obj->head->next;
		free(obj->head);
		obj->head = tmp;
	}
}

bool stackIsEmpty(STACK *obj)
{
	return (obj->head == NULL ? true : false);
}

void stackTop(STACK* obj, int *data, int *idx)
{
	if (obj->head != NULL)
	{
		*data = obj->head->data;
		*idx = obj->head->index;
	}
}

void stackFree(STACK* obj) {
	while (obj->head != NULL)
	{
		LIST_NODE *tmp = obj->head->next;
		free(obj->head);
		obj->head = tmp;
	}
	free(obj);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* T, int TSize, int* returnSize){
	int *ret = malloc(sizeof(int)*TSize);
	*returnSize = TSize;
	memset(ret, 0, sizeof(int)*TSize);

	STACK *s = stackCreate();
	stackPush(s, T[0], 0);   /* 1 <= length <= 30000 */
	for (int i = 1; i < TSize; i++)
	{
		int current = T[i];
		int topVal;
		int topIdx;
		stackTop(s, &topVal, &topIdx);

		while (topVal < current && !stackIsEmpty(s))
		{
			/* warmer case */
			stackPop(s);
			ret[topIdx] = i - topIdx;
			stackTop(s, &topVal, &topIdx);
		}
		stackPush(s, T[i], i);
	}
	stackFree(s);

	return ret;
}


