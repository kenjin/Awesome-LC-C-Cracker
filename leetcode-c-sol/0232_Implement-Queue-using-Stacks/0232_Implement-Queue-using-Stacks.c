/**

232. Implement Queue using Stacks [Easy]

Implement the following operations of a queue using stacks.

push(x) -- Push element x to the back of queue.
pop() -- Removes the element from in front of queue.
peek() -- Get the front element.
empty() -- Return whether the queue is empty.
Example:

MyQueue queue = new MyQueue();

queue.push(1);
queue.push(2);
queue.peek();  // returns 1
queue.pop();   // returns 1
queue.empty(); // returns false
Notes:

You must use only standard operations of a stack -- which means only 
push to top, peek/pop from top, size, and is empty operations are 
valid.

Depending on your language, stack may not be supported natively. You 
may simulate a stack by using a list or deque (double-ended queue), as 
long as you use only standard operations of a stack.

You may assume that all operations are valid (for example, no pop or 
peek operations will be called on an empty queue).

 */

struct linkedList
{
	int data;
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

void stackPush(STACK* obj, int val)
{
	/* Push and make the new node be the "head" of STACK*/
	LIST_NODE *node = malloc(sizeof(LIST_NODE));
	node->data = val;
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

int stackTop(STACK* obj)
{
	if (obj->head != NULL)
	{
		return obj->head->data;
	}
	return (-1);
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


enum
{
	MAIN_S = 0,
	BACK_S = 1,
};

typedef struct {
	STACK *s[2];
} MyQueue;

/** Initialize your data structure here. */
MyQueue* myQueueCreate() {
	STACK *s0= stackCreate();
	STACK *s1 = stackCreate();

	MyQueue *q = malloc(sizeof(MyQueue));
	q->s[MAIN_S] = s0;
	q->s[BACK_S] = s1;

	return q;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
	/* O(1) */
	stackPush(obj->s[MAIN_S], x);
}

void myQueueMoveStack(MyQueue* obj)
{
	/* Move main stack to back stack */
	while (!stackIsEmpty(obj->s[MAIN_S]))
	{
		int tmp = stackTop(obj->s[MAIN_S]);
		stackPop(obj->s[MAIN_S]);
		stackPush(obj->s[BACK_S], tmp);
	}
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
	/* O(n) */

	int ret = -1;
	if (myQueueEmpty(obj))
	{
		return ret;
	}

	/* Case: backup stack is empty "
	 *        main stack: [1 2 3]
	 *      backup stack: [ ] <= stack is empty
	 */
	if (stackIsEmpty(obj->s[BACK_S]))
	{
		/* If backup stack is empty, move the current to backup */
		myQueueMoveStack(obj);
	}

	ret = stackTop(obj->s[BACK_S]);
	stackPop(obj->s[BACK_S]);
	if (stackIsEmpty(obj->s[BACK_S]))
	{
		myQueueMoveStack(obj);
	}
	return ret;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
	/* O(n) */
	if (myQueueEmpty(obj))
	{
		return -1;
	} else
	{
		if (stackIsEmpty(obj->s[BACK_S]))
		{
			myQueueMoveStack(obj);
		}
		return stackTop(obj->s[BACK_S]);
	}
}

/** Returns whether the queue is empty. */
int myQueueEmpty(MyQueue* obj) {
	if ((stackIsEmpty(obj->s[MAIN_S])) && (stackIsEmpty(obj->s[BACK_S])))
	{
		return true;
	}
	return false;
}

void myQueueFree(MyQueue* obj) {
	stackFree(obj->s[MAIN_S]);
	stackFree(obj->s[BACK_S]);
	free(obj);
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);

 * int param_2 = myQueuePop(obj);

 * int param_3 = myQueuePeek(obj);

 * bool param_4 = myQueueEmpty(obj);

 * myQueueFree(obj);
 */
