static inline int transfer(char *s)
{
    int sum = 0;
    while (*s) {
        sum *= 10;
        sum += *s - '0';
        s++;
    }
    return sum;
}

int compareVersion(char *version1, char *version2)
{
    int len1 = strlen(version1);
    int len2 = strlen(version2);
    char **p1 = malloc(sizeof(char *) * len1);
    char **p2 = malloc(sizeof(char *) * len2);
    int ctr1 = 0, ctr2 = 0;

    char *delim = ".";
    char *ptr = NULL;
    ptr = strtok(version1, delim);
    while (ptr) {
        p1[ctr1] = ptr;
        ctr1++;
        ptr = strtok(NULL, delim);
    }

    ptr = strtok(version2, delim);
    while (ptr) {
        p2[ctr2] = ptr;
        ctr2++;
        ptr = strtok(NULL, delim);
    }

    int idx1 = 0, idx2 = 0, ret = 0;
    while (idx1 < ctr1 || idx2 < ctr2) {
        int tmp1 = 0, tmp2 = 0;
        if (idx1 < ctr1)
            tmp1 = transfer(p1[idx1]);

        if (idx2 < ctr2)
            tmp2 = transfer(p2[idx2]);

        if (tmp1 < tmp2) {
            ret = -1;
            break;
        } else if (tmp1 > tmp2) {
            ret = 1;
            break;
        }

        idx1++;
        idx2++;
    }

    free(p1);
    free(p2);
    return ret;
}