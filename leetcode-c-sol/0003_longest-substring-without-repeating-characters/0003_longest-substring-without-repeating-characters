int lengthOfLongestSubstring(char * s){
    int ascii[128] = {0};
    int head = 0, tail = 0, max = 0;
    while (s[tail]) {
        ascii[s[tail]]++;
        // Sequentially move the head pointer when finding a duplicate.
        while (ascii[s[tail]] > 1) {
            ascii[s[head]]--;
            head++;
        }
        max = (max > (tail-head+1) ? max : (tail-head+1));
        tail++;
    }

    return max;
}
