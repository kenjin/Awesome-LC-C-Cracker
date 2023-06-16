typedef struct __data {
    int ctr;
    char c;
} DATA;

static int compare(void *a, void *b)
{
    DATA n1 = *(DATA *)(a);
    DATA n2 = *(DATA *)(b);
    return n2.ctr - n1.ctr;
}

char * frequencySort(char * s){
    DATA d[256];
    char *ptr = s;

    for (int i = 0; i < 256; i++) {
        d[i].ctr = 0;
        d[i].c = i;
    }

    for (; *ptr; ptr++)
        d[*ptr].ctr++;

    qsort(d, 256, sizeof(DATA), compare);
    int ctr = 0, idx = 0;
    for (; d[idx].ctr; idx++) {
        while (d[idx].ctr--)
            s[ctr++] = d[idx].c;        
    }

    return s;
}
