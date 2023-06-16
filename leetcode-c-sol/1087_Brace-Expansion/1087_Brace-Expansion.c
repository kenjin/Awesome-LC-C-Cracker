#define MEM_ALLOC_UNIT (5000)

char *getCharSet(char *S, char *set)
{
    while (*S != '}') {
        if (*S != ',' && *S != ' ') {
            int curIdx = (*S <= 'Z') ? *S - 'A' : *S - 'a' + 26;
            set[curIdx] = 1;
        }
        S++;
    }
    return S;
}

void braceExpand(char *S, char *tmp, int tmpCtr, char ***ret, int *retSize)
{
    if (0 == *S) {
        if (*retSize % MEM_ALLOC_UNIT == 0) {
            *ret = realloc(*ret, sizeof(char *) * (*retSize + MEM_ALLOC_UNIT));
        }
        (*ret)[*retSize] = calloc(tmpCtr + 1, sizeof(char));
        strcpy((*ret)[*retSize], tmp);
        *retSize += 1;

        return;
    }

    char set[52] = {0};
    if (*S == '{') {
        S++;
        S = getCharSet(S, set);
        for (int i = 0; i < 52; i++) {
            if (set[i]) {
                tmp[tmpCtr] = (i < 26 ? 'A' + i : 'a' + i - 26);
                braceExpand(S + 1, tmp, tmpCtr + 1, ret, retSize);
            }
        }
    } else {
        tmp[tmpCtr] = *S;
        S++;
        braceExpand(S, tmp, tmpCtr + 1, ret, retSize);
    }
}

char **expand(char *S, int *returnSize)
{
    int len = strlen(S);
    char *tmp = calloc(len + 1, sizeof(char));
    int tmpIdx = 0;
    char **ret = malloc(sizeof(char *));
    *returnSize = 0;

    braceExpand(S, tmp, 0, &ret, returnSize);
    free(tmp);
    return ret;
}
