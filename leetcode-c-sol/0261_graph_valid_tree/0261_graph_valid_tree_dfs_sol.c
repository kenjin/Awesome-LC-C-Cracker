typedef struct __list
{
    int idx;
    struct __list *next;
} list_t;

static bool dfs(list_t *g, char *v, int curr, int prev)
{
    if (v[curr])
        return false;

    v[curr] = 1;
    list_t *node = g[curr].next;
    while (node) {
        if (node->idx != prev) {
            if (!dfs(g, v, node->idx, curr))
                return false;
        }
        node = node->next;
    }
    return true;
}

bool validTree(int n, int** edges, int edgesSize, int* edgesColSize)
{
    char *visited = calloc(n, sizeof(char));
    list_t *g = calloc(n, sizeof(list_t));
    for (int i = 0; i < edgesSize; i++) {
        list_t *n1 = malloc(sizeof(list_t));
        list_t *n2 = malloc(sizeof(list_t));
        n1->idx = edges[i][1];
        n1->next = g[edges[i][0]].next;
        n2->idx = edges[i][0];
        n2->next = g[edges[i][1]].next;
        g[edges[i][0]].next = n1;
        g[edges[i][1]].next = n2;
    }

    bool ret = true;
    if (!dfs(g, visited, 0, -1)) {
        ret = false;
    } else {
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                ret = false;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        list_t *head = g[i].next;
        while (head) {
            list_t *tmp = head;
            head = head->next;
            free(tmp);
        }
    }
    free(g);
    free(visited);
    return ret;
}
