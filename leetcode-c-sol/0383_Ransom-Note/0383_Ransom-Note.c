

bool canConstruct(char *ransomNote, char *magazine)
{
    int *set = calloc(26, sizeof(int));
    while (*magazine) {
        set[*magazine - 'a'] += 1;
        magazine++;
    }

    bool ret = true;
    while (*ransomNote) {
        if (set[*ransomNote - 'a'] == 0) {
            ret = false;
            break;
        }
        set[*ransomNote - 'a'] -= 1;
        ransomNote++;
    }

    free(set);
    return ret;
}
