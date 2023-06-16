/**

155. Min Stack [Easy]

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.


Example:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.

*/



struct linkedList
{
    int data;
    /* Be used to store the min for "current" stack
     * Ex: [3(Min=3)] :Push 2  =>  [3(Min=3), 2(Min=2)] 
     *     [3(Min=3), 2(Min=2)] : Push 4 => [3(Min=3), 2(Min=2), 4(Min=2)] 
     */
    int min;
    struct linkedList *next; 
};
typedef struct linkedList LIST_NODE;

typedef struct 
{
    LIST_NODE *head;
} MinStack;

/** initialize your data structure here. */
MinStack* minStackCreate() {
    MinStack *obj = malloc(sizeof(MinStack));
    obj->head = NULL;         
    return obj;
}

void minStackPush(MinStack* obj, int x) 
{
    /* Push and make the new node be the "head" of MinStack*/
    LIST_NODE *node = malloc(sizeof(LIST_NODE));
    node->data = x;
    node->next = NULL;
    
    /* Update node position and min. */
    /* Case 1: First push */
    if (obj->head == NULL)
    {
        /* NULL => [Node1]->NULL */
        node->min = node->data;
        obj->head = node;
    } else
    /* Case 2: Already have node(s) */
    {
        /* [Node1]->NULL => [Node2]->[Node1]->NULL
         *  ^HEAD            ^New_Head  
         */
        node->min = (obj->head->min < node->data ? obj->head->min : node->data);
        node->next = obj->head;
        obj->head = node;
    }
}

void minStackPop(MinStack* obj) 
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

int minStackTop(MinStack* obj) {
    if (obj->head == NULL)
    {
        return -1;
    } else
    {
        return obj->head->data;
    }
}

int minStackGetMin(MinStack* obj) {
    if (obj->head == NULL)
    {
        return -1;
    } else
    {
        return obj->head->min;
    }
}

void minStackFree(MinStack* obj) {
    while (obj->head != NULL)
    {
        LIST_NODE *tmp = obj->head->next;
        free(obj->head);
        obj->head = tmp;
    }
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, x);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/

