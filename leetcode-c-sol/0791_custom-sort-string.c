/***

Approach: Hash

First, set up the hash table and sequence/duplicate information. Then, iterate
through the string 's' from the end and place characters that are not in the
'order' array into the hash table. Finally, for characters in the 'order' array,
place them at the beginning according to their sequence and duplicates.

***/

#define LOWERCASE_CH_NUM (26)
typedef struct {
    unsigned short seq : 8;
    unsigned short dup : 8;
} order_set_t;

char* customSortString(char* order, char* s) {
    char* s_set = calloc(LOWERCASE_CH_NUM, sizeof(char));
    for (int i = 0; s[i]; i++)
        s_set[s[i] - 'a'] += 1;

    order_set_t* order_set = calloc(LOWERCASE_CH_NUM, sizeof(order_set_t));
    int seq = 1;
    for (int i = 0; order[i]; i++) {
        int idx = order[i] - 'a';
        if (s_set[idx]) {
            order_set[idx].seq = seq;
            order_set[idx].dup = s_set[idx];
            seq += s_set[idx];
        }
    }

    int tail = strlen(s) - 1;
    for (int x = tail; x >= 0; x--) {
        if (!order_set[s[x] - 'a'].seq) {
            s[tail--] = s[x];
        }
    }

    for (int i = 0; i < LOWERCASE_CH_NUM; i++) {
        int pos = order_set[i].seq - 1;
        if (-1 != pos) {
            for (int j = 0; j < order_set[i].dup; j++)
                s[pos++] = 'a' + i;
        }
    }

    free(order_set);
    free(s_set);
    return s;
}
