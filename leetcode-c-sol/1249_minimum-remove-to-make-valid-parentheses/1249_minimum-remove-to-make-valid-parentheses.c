/***

Basic parenthesis problems:

Use a stack to record the indices of all left parentheses. When encountering a
right parenthesis, pop the stack to cancel out its corresponding left
parenthesis. If the current right parenthesis does not match logically (i.e.,
the stack has no corresponding left parenthesis), intentionally mark it. After
scanning through, if there are still existing left parentheses in the stack, it
indicates there are unmatched right parentheses. Mark them as well. The indices
marked for removal are the characters that need to be removed.

***/
char* minRemoveToMakeValid(char* s) {
    int len = strlen(s);
    int* l_parenthesis_idx = malloc(sizeof(int) * len);
    int l_ctr = 0;

    for (int i = 0; s[i]; i++) {
        if (s[i] == '(') {
            l_parenthesis_idx[l_ctr++] = i;
        } else if (s[i] == ')') {
            if (l_ctr > 0)
                l_parenthesis_idx[--l_ctr];
            else
                s[i] = ']';
        }
    }

    for (int i = 0; i < l_ctr; i++)
        s[l_parenthesis_idx[i]] = '[';

    int ctr = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] != '[' && s[i] != ']')
            s[ctr++] = s[i];
    }
    s[ctr] = 0;

    free(l_parenthesis_idx);
    return s;
}
