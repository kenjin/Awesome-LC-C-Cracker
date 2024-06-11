char* removeDuplicates(char* s) {
    int slen = strlen(s);
    char* stack = malloc(sizeof(char) * slen);
    int stack_ctr = 0;
    for (int i = 0; i < slen; i++) {
        if (stack_ctr == 0 || stack[stack_ctr - 1] != s[i])
            stack[stack_ctr++] = s[i];
        else
            stack_ctr--;
    }

    for (int i = 0; i < stack_ctr; i++)
        s[i] = stack[i];

    s[stack_ctr] = 0;
    free(stack);
    return s;
}
