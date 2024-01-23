int numberOfBeams(char** bank, int bankSize)
{
    int ret = 0, prev_nodes = 0;
    for (int i = 0; i < bankSize; i++) {
        int len = strlen(bank[i]), cur_nodes = 0;
        for (int j = 0; j < len; j++) {
            if (bank[i][j] == '1')
                cur_nodes++;
        }

        if (prev_nodes)
            ret += prev_nodes * cur_nodes;
        if (cur_nodes)
            prev_nodes = cur_nodes;
    }
    return ret;
}
