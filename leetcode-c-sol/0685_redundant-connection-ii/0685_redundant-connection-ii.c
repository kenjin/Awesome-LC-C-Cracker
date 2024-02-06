
static int get_root(int *root, int i)
{
    while (i != root[i]) {
        i = root[i];
        root[i] = root[i];
    }
    return i;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findRedundantDirectedConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize)
{
    int *ret = malloc(sizeof(int)*2);
    *returnSize = 2;

    int *root = calloc(edgesSize + 1, sizeof(int));
    // Used to record first edge and second edge that
    int fst[2] = {0}, sec[2] = {0};
    for (int i = 0; i < edgesSize; i++) {
        int src = edges[i][0];
        int dst = edges[i][1];
        /*
         * - Find the node(dst) with an indegree of 2
         * - Note that after finding the nodes with an indegree of 2, we need 
         *   to set edge[i][1] to 0. This effectively breaks the edge of the 
         *   last node that generates an indegree of 2.
         */
        if (root[dst] != 0) {
            fst[0] = root[dst];
            fst[1] = dst;
            sec[0] = src;
            sec[1] = dst;
            edges[i][1] = 0;
            break;
        } else {
            root[dst] = src;
        }
    }

    // Reset and do union again, to decide we need to remove first edge or second.
    for (int i = 1; i <= edgesSize; i++)
        root[i] = i;
    
    bool found = false;
    for (int i = 0; i < edgesSize; i++) {
        if (!edges[i][1])
            continue;

        int n0 = get_root(root, edges[i][0]);
        int n1 = get_root(root, edges[i][1]);
        // Find the cycle, directly return the current edge or first edge
        if (n0 == n1) {
            if (fst[0]) {
                ret[0] = fst[0];
                ret[1] = fst[1];
            } else {
                ret[0] = edges[i][0];
                ret[1] = edges[i][1];
            }
            found = true;
            break;
        }
        root[n1] = n0;
    }   
    
    if (!found) {
        ret[0] = sec[0];
        ret[1] = sec[1];    
    }
    
    free(root);
    return ret;
}
