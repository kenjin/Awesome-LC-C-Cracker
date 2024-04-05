char* makeGood(char* s) {
    int cur_idx = 0;
    for (int i = 0; s[i]; i++) {
        if (cur_idx && abs(s[i] - s[cur_idx - 1]) == 0b100000) {
            cur_idx--;
            continue;
        }
        s[cur_idx++] = s[i];
    }
    s[cur_idx] = 0;
    return s;
}
