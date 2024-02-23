
typedef struct __node {
    int edge_num;
    int** edges;
} node_t;

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

static int find_min_path_idx(int* dist, bool* set, int size) {
    int ret = -1, min = INT_MAX;
    for (int i = 0; i < size; i++) {
        if (!set[i] && dist[i] < min) {
            ret = i;
            min = dist[i];
        }
    }
    return ret;
}

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n,
                     int k) {
    node_t* ninfo = calloc(n, sizeof(node_t));
    for (int i = 0; i < n; i++) {
        ninfo[i].edges = malloc(sizeof(int*) * (n - 1));
        ninfo[i].edge_num = 0;
    }

    // Update edge info
    for (int i = 0; i < timesSize; i++) {
        int src = times[i][0] - 1; // 0-indexed
        int dst = times[i][1] - 1; // 0-indexed
        int cost = times[i][2];
        ninfo[src].edges[ninfo[src].edge_num] = times[i];
        ninfo[src].edge_num += 1;
    }

    int* dist = malloc(sizeof(int) * n);
    bool* spt_set = malloc(sizeof(bool) * n);
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        spt_set[i] = false;
    }

    dist[k - 1] = 0;
    int target = k - 1;
    while (target != -1) {
        spt_set[target] = true;
        for (int i = 0; i < ninfo[target].edge_num; i++) {
            int cur_dst = (ninfo[target].edges[i])[1] - 1; // 0-indexed
            int cur_cost = (ninfo[target].edges[i])[2];
            dist[cur_dst] = MIN(dist[cur_dst], dist[target] + cur_cost);
        }
        target = find_min_path_idx(dist, spt_set, n);
    }

    int ret = 0;
    for (int i = 0; i < n; i++) {
        if (!spt_set[i]) {
            ret = -1;
            break;
        }
        ret = MAX(ret, dist[i]);
    }

    free(spt_set);
    free(dist);
    free(ninfo);
    return ret;
}
