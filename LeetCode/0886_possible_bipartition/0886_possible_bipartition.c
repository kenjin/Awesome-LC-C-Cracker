
bool dfs(int **g, int gsize, int *colors, int cur, int c)
{
}

bool possibleBipartition(int N,
                         int **dislikes,
                         int dislikesSize,
                         int *dislikesColSize)
{
    char **g = malloc(sizeof(char *) * N);
    char *colors = malloc(sizeof(char) * N);
    for (int i = 0; i < N; i++) {
        g[i] = calloc(N, sizeof(char));
        colors[i] = -1;
    }

    for (int i = 0; i < dislikesSize; i++) {
        int l1 = dislikes[i][0];
        int l2 = dislikes[i][1];
        g[l1][l2] = g[l2][l1] = 1;
    }

    for (int i = 0; i < N; i++) {
        if (colors[i] == -1 && !dfs(g, N, colors, i, 1))
            return false;
    }

    for (int i = 0; i < N; i++)
        free(g[i]);
    free(g);
    free(colors);
    return true;
}