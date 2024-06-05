static int process_price(char* s, char* target, int* target_idx, int discount)
{
    double sum = 0;
    int idx = 0;
    while (s[idx] >= '0' && s[idx] <= '9') {
        sum *= 10;
        sum += s[idx] - '0';
        idx++;
    }

    if (idx > 0) {
        if (s[idx] == ' ' || s[idx] == 0) {
            *target_idx += sprintf(&target[*target_idx], "%.2lf",
                                   sum * (100 - discount) / 100);
        } else {
            memcpy(&target[*target_idx], s, sizeof(char) * idx);
            *target_idx += idx;
        }
        return idx;
    }
    return 0;
}

char* discountPrices(char* sentence, int discount)
{
    int len = strlen(sentence), ret_idx = 0, sum = 0;
    char* ret = malloc(sizeof(char) * ((len << 1) + 3));
    for (int x = 0; sentence[x] != 0; x++) {
        ret[ret_idx++] = sentence[x];
        if (sentence[x] == '$' && (x == 0 || sentence[x - 1] == ' '))
            x += process_price(&(sentence[x + 1]), ret, &ret_idx, discount);
    }
    ret[ret_idx] = 0;
    return ret;
}
