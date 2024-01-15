typedef struct __node {
    int used;
    int in;
    int out[26];
    int out_ctr;
} node_t;

typedef struct __queue
{
    int size;
    int cur;
    int front;
    int rear;
    int *p;
} queue_t;

queue_t* createq(int size)
{
    queue_t *obj = malloc(sizeof(queue_t));
    obj->size = size;
    obj->cur = 0;
    obj->front = 0;
    obj->rear = 0;
    obj->p = malloc(sizeof(int)*size);
    return obj;
}

void destroyq(queue_t *obj)
{
    free(obj->p);
    free(obj);
}

bool is_emptyq(queue_t *obj)
{
    return (obj->cur == 0);
}

void addq(queue_t *obj, int idx)
{
    obj->p[obj->rear] = idx;
    obj->rear = (obj->rear+1) % obj->size;
    obj->cur++;
}

int delq(queue_t *obj)
{
    int ret = obj->p[obj->front];
    obj->front = (obj->front+1) % obj->size;
    obj->cur--;
    return ret;
}

char* alienOrder(char** words, int wordsSize)
{
    node_t *n = calloc(26, sizeof(node_t));
    char *ret = calloc(27, sizeof(char));
    int ret_ctr = 0, words_chars = 0;

    // It is used to record the valid edge
    char **sort_data = malloc(sizeof(char*)*26);
    for (int i = 0; i < 26; i++)
        sort_data[i] = calloc(26, sizeof(char));

    // Init: collect all the char from words
    for (int i = 0; i < wordsSize; i++) {
        char *tmp = words[i];
        while (*tmp){
            if (!n[*tmp - 'a'].used) {
                words_chars++;
                n[*tmp - 'a'].used = 1;        
            }
            tmp++;
        }
    }

    // Gen a directed graph
    for (int i = 1; i < wordsSize; i++) {
        int len1 = strlen(words[i-1]);
        int len2 = strlen(words[i]);
        for (int x = 0; x < len1; x++) {
            // Invalid case: ["abc","ab"]
            if (!words[i][x]) {
                ret_ctr = -1;
                goto out;
            }
            int src_idx = words[i-1][x]-'a';
            int dst_idx = words[i][x]-'a';
            if (src_idx != dst_idx) {
                if (sort_data[dst_idx][src_idx]) {
                    // Invalid case: ["ax", "xa"]
                    ret_ctr = -1;
                    goto out;
                }
                n[src_idx].out[n[src_idx].out_ctr] = dst_idx;
                n[src_idx].out_ctr += 1;
                n[dst_idx].in  += 1;
                sort_data[src_idx][dst_idx] = 1;
                break;
            }
        }
    }

    queue_t *q = createq(26);
    for (int i = 0; i < 26; i++) {
        if (n[i].used && !n[i].in)
            addq(q, i);
    }

    while (!is_emptyq(q)) {
        int cur_idx = delq(q);
        ret[ret_ctr++] = cur_idx +'a';
        for (int x = 0; x < n[cur_idx].out_ctr; x++) {
            int tmp = n[cur_idx].out[x];
            n[tmp].in--;
            if (!n[tmp].in)
                addq(q, tmp);
        }
    }
    destroyq(q);
out:
    for (int i = 0; i < 26; i++)
        free(sort_data[i]);
    free(sort_data);
    free(n);
    return (words_chars == ret_ctr) ? ret : "";
}
