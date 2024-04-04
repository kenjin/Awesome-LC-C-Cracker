int maxDepth(char* s)
{
    int ret = 0, ctr = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '(') {
            ctr++;
            ret = (ret > ctr ? ret : ctr);
        } else if (s[i] == ')') {
            ctr--;
        }
    }
    return ret;
}
