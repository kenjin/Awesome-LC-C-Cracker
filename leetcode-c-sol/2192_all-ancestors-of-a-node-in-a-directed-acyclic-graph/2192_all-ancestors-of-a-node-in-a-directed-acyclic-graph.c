/***

Approach: DFS

Solved this problem using a method similar to reverse DFS. The task is to find
the ancestors of each node in the graph. Since the graph itself is a Directed
Acyclic Graph (DAG), and each edge has a direction, we can reverse the direction
of each edge when building the graph to find the ancestors. For example, if
there is an edge from A to B, we can add A to the adjacency list of B when
constructing the graph. This means that if we start from B, we can reach its
ancestor A.

***/

static void dfs(int** graph, int* graph_col_sz, char* visited, int u) {
    visited[u] = 1;
    for (int i = 0; i < graph_col_sz[u]; i++) {
        int v = graph[u][i];
        if (!visited[v])
            dfs(graph, graph_col_sz, visited, v);
    }
}

int** getAncestors(int n, int** edges, int edges_sz, int* edges_col_sz, int* return_sz, int** return_col_sz)
{
    int** graph = (int**)malloc(n * sizeof(int*));
    int* graph_col_sz = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
        graph_col_sz[i] = 0;
    }

    for (int i = 0; i < edges_sz; i++) {
        int from = edges[i][0];
        int to = edges[i][1];
        graph[to][graph_col_sz[to]++] = from;
    }

    int** res = (int**)malloc(n * sizeof(int*));
    *return_col_sz = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        res[i] = (int*)malloc(n * sizeof(int));
        (*return_col_sz)[i] = 0;
    }

    char* visited = (char*)malloc(n * sizeof(char));

    for (int i = 0; i < n; i++) {
        memset(visited, 0, n * sizeof(char));
        dfs(graph, graph_col_sz, visited, i);
        visited[i] = 0;
        for (int j = 0; j < n; j++) {
            if (visited[j])
                res[i][(*return_col_sz)[i]++] = j;
        }
    }

    for (int i = 0; i < n; i++)
        free(graph[i]);
    free(graph);
    free(graph_col_sz);
    free(visited);
    *return_sz = n;
    return res;
}

