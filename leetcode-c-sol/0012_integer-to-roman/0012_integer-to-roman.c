typedef struct {
    int val;
    char sym;
} TRANSLATE;

#define MAX_SYMBOL 7

char *intToRoman(int num)
{
    TRANSLATE d[MAX_SYMBOL] = {{1, 'I'},   {5, 'V'},   {10, 'X'},  {50, 'L'},
                               {100, 'C'}, {500, 'D'}, {1000, 'M'}};

    char *ret = calloc(30, sizeof(char));
    int ctr = 0;
    for (int x = MAX_SYMBOL - 1; x >= 0; x--) {
        int tmp = num / d[x].val;
        num %= d[x].val;
        /*  9 case */
        if (x > 0 && tmp == 1 && (num / d[x - 1].val == 4)) {
            ret[ctr] = d[x - 1].sym;
            ret[ctr + 1] = d[x + 1].sym;
            ctr += 2;
            num %= d[x - 1].val;
            continue;
        }
        /* 4 case */
        if (tmp == 4) {
            ret[ctr] = d[x].sym;
            ret[ctr + 1] = d[x + 1].sym;
            ctr += 2;
            num %= d[x].val;
            continue;
        }

        while (tmp > 0) {
            ret[ctr] = d[x].sym;
            ctr++;
            tmp--;
        }
    }
    return ret;
}
