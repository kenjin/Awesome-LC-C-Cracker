
bool dfs(int **adj_matrix, int *chk, int *visit, int node, int cur)
{
    if (chk[cur])
        return true;
    if (visit[cur])
        return false;

    visit[cur] = 1;
    for (int i = 0; i < node; i++) {
        if (adj_matrix[cur][i]) {
            if (dfs(adj_matrix, chk, visit, node, i))
                chk[i] = 1;
            else
                return false;
        }
    }

    chk[cur] = 1;
    return true;
}

bool canFinish(int numCourses,
               int **prerequisites,
               int prerequisitesSize,
               int *prerequisitesColSize)
{
    int **adj_matrix = malloc(sizeof(int *) * numCourses);
    int *chk = calloc(numCourses, sizeof(int));
    int *visit = calloc(numCourses, sizeof(int));
    for (int i = 0; i < numCourses; i++)
        adj_matrix[i] = calloc(numCourses, sizeof(int));

    for (int i = 0; i < prerequisitesSize; i++)
        adj_matrix[prerequisites[i][0]][prerequisites[i][1]] = 1;

    bool ret = true;
    for (int i = 0; i < numCourses; i++) {
        memset(visit, 0, sizeof(int) * numCourses);
        if (!dfs(adj_matrix, chk, visit, numCourses, i)) {
            ret = false;
            break;
        }
    }

    free(chk);
    free(visit);
    for (int i = 0; i < numCourses; i++)
        free(adj_matrix[i]);
    free(adj_matrix);

    return ret;
}
