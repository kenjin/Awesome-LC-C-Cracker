#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline();
char **split_string(char *);

static int bsearch_leq(int *a, int n, int value)
{
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (a[mid] > value) {
            high = mid - 1;
        } else {
            if ((mid == n - 1) || (a[mid + 1] > value))
                return mid;
            else
                low = mid + 1;
        }
    }
    return -1;
}

int merge_wo_dup(int *a, int head, int tail)
{
    if (head >= tail)
        return (head == tail ? 1 : 0);

    int mid = ((tail - head) >> 1) + head;
    int l_ret = merge_wo_dup(a, head, mid);
    int r_ret = merge_wo_dup(a, mid + 1, tail);
    int *tmp = malloc(sizeof(int) * (l_ret + r_ret));
    int tmp_ctr = 0, l_ctr = 0, r_ctr = 0;
    while (l_ctr < l_ret && r_ctr < r_ret) {
        int l_idx = head + l_ctr;
        int r_idx = mid + 1 + r_ctr;
        if (a[l_idx] < a[r_idx]) {
            tmp[tmp_ctr++] = a[l_idx];
            l_ctr++;
        } else if (a[l_idx] > a[r_idx]) {
            tmp[tmp_ctr++] = a[r_idx];
            r_ctr++;
        } else {
            if (tmp_ctr == 0 || tmp[tmp_ctr] != a[r_idx])
                tmp[tmp_ctr++] = a[r_idx];
            l_ctr++;
            r_ctr++;
        }
    }

    while (l_ctr < l_ret) {
        int l_idx = head + l_ctr;
        if (tmp_ctr == 0 || tmp[tmp_ctr] != a[l_idx])
            tmp[tmp_ctr++] = a[l_idx];
        l_ctr++;
    }

    while (r_ctr < r_ret) {
        int r_idx = mid + 1 + r_ctr;
        if (tmp_ctr == 0 || tmp[tmp_ctr] != a[r_idx])
            tmp[tmp_ctr++] = a[r_idx];
        r_ctr++;
    }

    memcpy(&a[head], tmp, sizeof(int) * tmp_ctr);
    free(tmp);
    return tmp_ctr;
}

// Complete the triplets function below.
long triplets(int a_count, int *a, int b_count, int *b, int c_count, int *c)
{
    a_count = merge_wo_dup(a, 0, a_count - 1);
    b_count = merge_wo_dup(b, 0, b_count - 1);
    c_count = merge_wo_dup(c, 0, c_count - 1);

    long sum = 0;
    for (int i = 0; i < b_count; i++) {
        if (i != 0 && b[i] == b[i - 1])
            continue;

        int idx1 = bsearch_leq(a, a_count, b[i]);
        int idx2 = bsearch_leq(c, c_count, b[i]);
        if (idx1 == -1 || idx2 == -1)
            continue;

        sum += ((long) (idx1 + 1) * (long) (idx2 + 1));
    }

    return sum;
}

int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char **lenaLenbLenc = split_string(readline());

    char *lena_endptr;
    char *lena_str = lenaLenbLenc[0];
    int lena = strtol(lena_str, &lena_endptr, 10);

    if (lena_endptr == lena_str || *lena_endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    char *lenb_endptr;
    char *lenb_str = lenaLenbLenc[1];
    int lenb = strtol(lenb_str, &lenb_endptr, 10);

    if (lenb_endptr == lenb_str || *lenb_endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    char *lenc_endptr;
    char *lenc_str = lenaLenbLenc[2];
    int lenc = strtol(lenc_str, &lenc_endptr, 10);

    if (lenc_endptr == lenc_str || *lenc_endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    char **arra_temp = split_string(readline());

    int *arra = malloc(lena * sizeof(int));

    for (int i = 0; i < lena; i++) {
        char *arra_item_endptr;
        char *arra_item_str = *(arra_temp + i);
        int arra_item = strtol(arra_item_str, &arra_item_endptr, 10);

        if (arra_item_endptr == arra_item_str || *arra_item_endptr != '\0') {
            exit(EXIT_FAILURE);
        }

        *(arra + i) = arra_item;
    }

    int arra_count = lena;

    char **arrb_temp = split_string(readline());

    int *arrb = malloc(lenb * sizeof(int));

    for (int i = 0; i < lenb; i++) {
        char *arrb_item_endptr;
        char *arrb_item_str = *(arrb_temp + i);
        int arrb_item = strtol(arrb_item_str, &arrb_item_endptr, 10);

        if (arrb_item_endptr == arrb_item_str || *arrb_item_endptr != '\0') {
            exit(EXIT_FAILURE);
        }

        *(arrb + i) = arrb_item;
    }

    int arrb_count = lenb;

    char **arrc_temp = split_string(readline());

    int *arrc = malloc(lenc * sizeof(int));

    for (int i = 0; i < lenc; i++) {
        char *arrc_item_endptr;
        char *arrc_item_str = *(arrc_temp + i);
        int arrc_item = strtol(arrc_item_str, &arrc_item_endptr, 10);

        if (arrc_item_endptr == arrc_item_str || *arrc_item_endptr != '\0') {
            exit(EXIT_FAILURE);
        }

        *(arrc + i) = arrc_item;
    }

    int arrc_count = lenc;

    long ans = triplets(arra_count, arra, arrb_count, arrb, arrc_count, arrc);

    fprintf(fptr, "%ld\n", ans);

    fclose(fptr);

    return 0;
}

char *readline()
{
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char *data = malloc(alloc_length);

    while (true) {
        char *cursor = data + data_length;
        char *line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char **split_string(char *str)
{
    char **splits = NULL;
    char *token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char *) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
