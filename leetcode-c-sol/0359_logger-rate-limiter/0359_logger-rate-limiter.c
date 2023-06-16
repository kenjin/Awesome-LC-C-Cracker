#define HASH_SIZE 500

typedef struct __node {
    int time;
    char *msg;
    struct __node *next;
} NODE;

typedef struct {
    NODE **bucket;
    int size;
} Logger;


/** Initialize your data structure here. */
Logger *loggerCreate()
{
    Logger *obj = malloc(sizeof(Logger));
    obj->bucket = calloc(HASH_SIZE, sizeof(NODE *));
    obj->size = HASH_SIZE;
    return obj;
}

static int hash(Logger *obj, char *str)
{
    size_t hash = 5381;
    while (*str)
        hash = 33 * hash ^ (unsigned char) *str++;

    return hash % obj->size;
}

bool logger_is_legal(Logger *obj, char *msg, int time)
{
    int hash_idx = hash(obj, msg);
    NODE *cur = obj->bucket[hash_idx];
    while (cur) {
        if (!strcmp(cur->msg, msg)) {
            if (time - cur->time >= 10)
                return true;
            else
                return false;
        }
        cur = cur->next;
    }

    return true;
}

void logger_update(Logger *obj, char *msg, int time)
{
    int msg_len = strlen(msg);
    int hash_idx = hash(obj, msg);
    NODE *cur = obj->bucket[hash_idx], *prev = NULL;
    while (cur) {
        if (!strcmp(cur->msg, msg)) {
            /* Update time */
            cur->time = time;
            return;
        }
        prev = cur;
        cur = cur->next;
    }

    NODE *new_node = malloc(sizeof(NODE));
    new_node->time = time;
    new_node->next = NULL;
    new_node->msg = calloc(msg_len + 1, sizeof(char));
    strcpy(new_node->msg, msg);
    if (!prev) /* Empty bucket, add it directly */
        obj->bucket[hash_idx] = new_node;
    else
        prev->next = new_node;
}

/** Returns true if the message should be printed in the given timestamp,
  otherwise returns false.
  If this method returns false, the message will not be printed.
  The timestamp is in seconds granularity. */
bool loggerShouldPrintMessage(Logger *obj, int timestamp, char *message)
{
    bool ret = logger_is_legal(obj, message, timestamp);
    if (!ret)
        return false;

    logger_update(obj, message, timestamp);
    return true;
}

void loggerFree(Logger *obj)
{
    for (int i = 0; i < obj->size; i++) {
        NODE *tmp = obj->bucket[i];
        while (tmp != NULL) {
            NODE *next_node = tmp->next;
            free(tmp->msg);
            free(tmp);
            tmp = next_node;
        }
    }
    free(obj->bucket);
    free(obj);
}

/**
 * Your Logger struct will be instantiated and called as such:
 * Logger* obj = loggerCreate();
 * bool param_1 = loggerShouldPrintMessage(obj, timestamp, message);

 * loggerFree(obj);
 */
