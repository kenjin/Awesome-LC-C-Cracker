
char* firstPalindrome(char** words, int wordsSize) {
    for (int i = 0; i < wordsSize; i++) {
        int head = 0, tail = strlen(words[i]) - 1;
        bool found = true;
        while (head < tail) {
            if (words[i][head] != words[i][tail]) {
                found = false;
                break;
            }
            head++;
            tail--;
        }
        if (found)
            return words[i];
    }
    return "";
}
