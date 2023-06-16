#define RECV_PAST_SEC 300

typedef struct listNode
{
	int sec;
	struct listNode *next;
} NODE;

typedef struct 
{
	int timeSize;    
	NODE *head;
	NODE *tail;
} HitCounter;

/** Initialize your data structure here. */
HitCounter* hitCounterCreate() 
{
	HitCounter *obj = calloc(1, sizeof(HitCounter));
	return obj;    
}

/** Record a hit.
  @param timestamp - The current timestamp (in seconds granularity). */
void hitCounterHit(HitCounter* obj, int timestamp) 
{
	obj->timeSize += 1;

	NODE *newNode = calloc(1, sizeof(NODE));
	newNode->sec = timestamp;
	if (NULL != obj->tail)
	{
		obj->tail->next = newNode;
		obj->tail = obj->tail->next;
	} else
	{
		obj->head = newNode;
	}
	obj->tail = newNode;
}

/** Return the number of hits in the past 5 minutes.
  @param timestamp - The current timestamp (in seconds granularity). */
int hitCounterGetHits(HitCounter* obj, int timestamp) 
{
	int limit = (timestamp < RECV_PAST_SEC ? 0 : timestamp - RECV_PAST_SEC);
	NODE *root = obj->head;
	while (root)
	{
		if (root->sec <= limit)
		{
			NODE *tmpDel = root;
			root = root->next;   
			obj->timeSize -= 1;            
			free(tmpDel);
		} else
		{
			break;
		}
	}    
	// Concact the time-valid list
	obj->head = root;
	// Empty list case
	if (NULL == obj->head)
	{
		obj->tail = NULL;
	}

	return obj->timeSize;
}

void hitCounterFree(HitCounter* obj) 
{
	NODE *root = obj->head;
	while (root)
	{
		NODE *tmpDel = root;
		root = root->next;           
		free(tmpDel);
	}
	free(obj);
}

/**
 * Your HitCounter struct will be instantiated and called as such:
 * HitCounter* obj = hitCounterCreate();
 * hitCounterHit(obj, timestamp);

 * int param_2 = hitCounterGetHits(obj, timestamp);

 * hitCounterFree(obj);
 */
