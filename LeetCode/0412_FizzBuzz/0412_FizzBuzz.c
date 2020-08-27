

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **fizzBuzz(int n, int *return_sz)
{
    char **ret = malloc(sizeof(char *) * n);
    *return_sz = n;
    int def_sz = (n < 5 ? 5 : n + 1);

    for (int i = 1; i <= n; i++) {
        ret[i - 1] = calloc(def_sz, sizeof(char));
        if (0 == i % 3)
            strcat(ret[i - 1], "Fizz");
        if (0 == i % 5)
            strcat(ret[i - 1], "Buzz");
        if (0 != i % 5 && 0 != i % 3)
            sprintf(ret[i - 1], "%d", i);
    }

    return ret;
}