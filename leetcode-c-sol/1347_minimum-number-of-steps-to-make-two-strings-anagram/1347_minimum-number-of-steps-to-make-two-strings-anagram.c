int minSteps(char* s, char* t) {
    int set1[26] = {0};
    int set2[26] = {0};

    while (*s) {
        set1[*s - 'a']++;
        s++;
    }
    while (*t) {
        set2[*t - 'a']++;
        t++;
    }

    int sum = 0;
    for (int i = 0; i < 26; i++) {
        if (set1[i] > set2[i])
            sum += (set1[i] - set2[i]);
    }
}

