/**

707. Design Linked List [Easy]

Design your implementation of the linked list. You can choose to use the
singly linked list or the doubly linked list. A node in a singly linked 
list should have two attributes: val and next. val is the value of the 
current node, and next is a pointer/reference to the next node. If you 
want to use the doubly linked list, you will need one more attribute 
prev to indicate the previous node in the linked list. Assume all nodes 
in the linked list are 0-indexed.

Implement these functions in your linked list class:

get(index) : Get the value of the index-th node in the linked list. 
             If the index is invalid, return -1.
addAtHead(val) : Add a node of value val before the first element of the
                 linked list. After the insertion, the new node will be 
				 the first node of the linked list.
addAtTail(val) : Append a node of value val to the last element of the 
                 linked list.
addAtIndex(index, val) : Add a node of value val before the index-th 
                         node in the linked list. If index equals to the
						 length of linked list, the node will be 
						 appended to the end of linked list. If index is
						 greater than the length, the node will not be
						 inserted.
deleteAtIndex(index) : Delete the index-th node in the linked list, if
                       the index is valid.


Example:

MyLinkedList linkedList = new MyLinkedList();
linkedList.addAtHead(1);
linkedList.addAtTail(3);
linkedList.addAtIndex(1, 2);  // linked list becomes 1->2->3
linkedList.get(1);            // returns 2
linkedList.deleteAtIndex(1);  // now the linked list is 1->3
linkedList.get(1);            // returns 3


Note:

All values will be in the range of [1, 1000].
The number of operations will be in the range of [1, 1000].
Please do not use the built-in LinkedList library.

*/


typedef struct listNode NODE;

struct listNode
{
	int val;
	NODE *prev;
	NODE *next;
};

typedef struct 
{
	NODE *head;    
} MyLinkedList;

/** Initialize your data structure here. */

MyLinkedList* myLinkedListCreate() 
{
	MyLinkedList *obj = malloc(sizeof(MyLinkedList));
	obj->head = NULL;
	return obj;
}

/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
int myLinkedListGet(MyLinkedList* obj, int index) 
{
	NODE *root = obj->head;    
	int current = 0;

	while (root != NULL)
	{
		if (index == current)
		{
			return root->val;
		}
		current++;
		root = root->next;
	}
	return -1;
}

NODE* createNode(int value)
{
	NODE *newNode = malloc(sizeof(NODE));
	newNode->val = value; 
	newNode->next = newNode->prev = NULL;

	return newNode;
}

/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
void myLinkedListAddAtHead(MyLinkedList* obj, int val) 
{
	NODE *newNode = createNode(val);

	/* Empty List */
	if (obj->head == NULL)
	{
		obj->head = newNode;
	} else
		/* Non-empty List */
	{
		// before: NULL <- [OriR]  ->  NULL
		//  after: NULL <- [NewR] "->" [OriR] ->NULL
		//                "<-"
		NODE *tmp = obj->head;
		obj->head = newNode;
		obj->head->next = tmp;
		tmp->prev = obj->head;
	}
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, int val) 
{
	NODE *newNode = createNode(val);

	/* Empty List */
	if (obj->head == NULL)
	{
		// before: NULL
		//  after: NULL <- [OriR] ->NULL
		// 
		obj->head = newNode;
	} else
		/* Non-empty List */
	{
		NODE *tmp = obj->head;
		NODE *pre = NULL;
		while (tmp != NULL)
		{            
			pre = tmp;
			tmp = tmp->next;
		}
		// NULL <- [OriR]  ->  NULL
		// NULL <- [OriR] "->" [NewR] ->  NULL
		//                "<-"       "->"
		//          ^pre                   ^tmp

		pre->next = newNode; 
		newNode->next = tmp;
		newNode->prev = pre;
	}
}

/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) 
{    
	/* Case: Head */
	if (index <= 0)
	{
		myLinkedListAddAtHead(obj, val);
	} else /* Case: Index > 0*/
	{
		int current = 0;
		NODE *root = obj->head;
		NODE *pre = NULL; 
		while (root != NULL)
		{
			if (current == index)
			{
				NODE *newNode = createNode(val);
				/* Non-empty List */
				// NULL <- [pre]  <->  [root] -> NULL
				// NULL <- [pre]  "->" [NewR] "<-" [root] -> NULL
				//                "<-"        "->"                    
				pre->next = newNode;        
				root->prev = newNode;
				newNode->next = root;
				newNode->prev = pre;
				return;            
			}
			current++;     
			pre = root;
			root = root->next;
		}        
		/* Check the index is at tail(NULL) */
		if (current == index)
		{            
			myLinkedListAddAtTail(obj, val);            
		}
	}
}

/** Delete the index-th node in the linked list, if the index is valid. */
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) 
{
	/* Case: Head(aka index=0) */
	if (index == 0)
	{
		if (obj->head != NULL)
		{
			NODE *tmp = obj->head->next;
			free(obj->head);
			obj->head = tmp;
		}                
	} else /* Case: Index > 0*/
	{
		int current = 0;
		NODE *root = obj->head;
		while (root != NULL)
		{
			if (current == index)
			{
				/* Tail Case */
				if (root->next == NULL) 
				{
					/* Non-empty List */
					// before: NULL <- ...[pre]  <->  [cur] -> NULL
					//  after: NULL <- ...[pre]  "->" NULL                    
					root->prev->next = NULL; // pre->next = NULL                    
					free(root);                    
				}
				else /* General Case */ 
				{
					/* Non-empty List */
					// NULL <- [AAA]  <->  [cur] <-> [BBB] -> NULL
					// NULL <- [AAA] "<->" [BBB] -> NULL
					//              
					root->next->prev = root->prev;        
					root->prev->next = root->next;
					free(root);
				}
				return;            
			}
			current++;
			root = root->next;
		}
	}
}

void myLinkedListFree(MyLinkedList* obj) 
{
	NODE *root = obj->head;

	while (root != NULL)
	{
		NODE *tmp = root->next;
		free(root);
		root = tmp;
	}
	free(obj);
}

/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);

 * myLinkedListAddAtHead(obj, val);

 * myLinkedListAddAtTail(obj, val);

 * myLinkedListAddAtIndex(obj, index, val);

 * myLinkedListDeleteAtIndex(obj, index);

 * myLinkedListFree(obj);
 */
