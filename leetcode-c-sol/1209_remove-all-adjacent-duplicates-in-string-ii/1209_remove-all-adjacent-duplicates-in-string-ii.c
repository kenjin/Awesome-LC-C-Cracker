/***

Approach: Stack

We define a structure data_t to store characters (ch) and their consecutive
occurrence counts (consec_occ). Then, we initialize a stack (stk) to store
characters and their consecutive occurrence counts. We iterate through each
character in the input string s, pushing the current character onto the stack
with a consecutive occurrence count of 1 if the stack is empty or if the current
character is different from the top character of the stack. If the current
character is the same as the top character of the stack, we increment its
consecutive occurrence count unless it equals k - 1, in which case we pop it
from the stack.

***/

typedef struct {
    char ch;
    int consec_occ;
} data_t;

char* removeDuplicates(char* s, int k) {
    int slen = strlen(s), stk_ctr = 0;
    data_t* stk = malloc(sizeof(data_t) * slen);

    for (int i = 0; i < slen; i++) {
        if (stk_ctr == 0 || s[i] != stk[stk_ctr - 1].ch) {
            stk[stk_ctr].ch = s[i];
            stk[stk_ctr++].consec_occ = 1;
        } else {
            // The top element is the same as current ch and continues for k-1
            // consecutive occurrences.
            if (stk[stk_ctr - 1].consec_occ == k - 1)
                stk_ctr--;
            else
                stk[stk_ctr - 1].consec_occ += 1;
        }
    }

    int sidx = 0;
    for (int i = 0; i < stk_ctr; i++) {
        while (stk[i].consec_occ) {
            s[sidx++] = stk[i].ch;
            stk[i].consec_occ -= 1;
        }
    }
    s[sidx] = 0;

    free(stk);
    return s;
}
