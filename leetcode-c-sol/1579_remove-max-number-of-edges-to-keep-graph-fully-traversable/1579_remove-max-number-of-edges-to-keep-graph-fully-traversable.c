/***

Approach: Disjoint Set Union(DSU)

Initialization: We create two arrays bob and alice to represent the union-find
struct for Bob and Alice respectively. Each node initially points to itself,
indicating that each node is its own parent.

Sorting Edges: We sort the edges in descending order based on their type. This
ensures that type 3 edges (usable by both Bob and Alice) are processed first,
followed by type 2 edges (Bob only) and type 1 edges (Alice only).

Processing Edges:
For each edge,
- If the edge is type 3 (both Bob and Alice), we attempt to union the nodes in
  both bob and alice structures. If either union operation fails (nodes are
  already connected), it means the edge is redundant and can be removed.
- If the edge is type 1 (Alice only), we only attempt to union the nodes in the
  alice structure. If the union operation fails, the edge is redundant.
- If the edge is type 2 (Bob only), we only attempt to union the nodes in the
  bob structure. If the union operation fails, the edge is redundant.

Checking Connectivity: After processing all the edges, we check if all nodes
are connected in both alice and bob structures. If any node is not connected,
it's impossible to connect all nodes with the given edges, and we return -1.

Counting Redundant Edges: The variable ans keeps track of the number of
redundant edges that can be removed.

***/

static int cmp_edges(const void* a, const void* b) {
    int* edgeA = *(int**)a;
    int* edgeB = *(int**)b;
    return edgeB[0] - edgeA[0];
}

static int find(int i, int* parent) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[parent[i]], parent);
}

static int merge(int a, int b, int* parent) {
    a = find(a, parent);
    b = find(b, parent);
    if (a == b)
        return 0;
    parent[b] = a;
    return 1;
}

int maxNumEdgesToRemove(int n, int** edges, int edges_sz, int* edges_col_sz) {
    int* bob = (int*)malloc((n + 1) * sizeof(int));
    int* alice = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; ++i) {
        bob[i] = i;
        alice[i] = i;
    }

    qsort(edges, edges_sz, sizeof(int*), cmp_edges);

    int ans = 0;
    for (int i = 0; i < edges_sz; ++i) {
        int* e = edges[i];
        if (e[0] == 1) {
            if (!merge(e[1], e[2], alice))
                ans++;
        } else if (e[0] == 2) {
            if (!merge(e[1], e[2], bob))
                ans++;
        } else {
            merge(e[1], e[2], alice);
            if (!merge(e[1], e[2], bob))
                ans++;
        }
    }

    int a = find(alice[n], alice);
    int b = find(bob[n], bob);
    for (int i = 1; i < n; ++i) {
        if (a != find(alice[i], alice) || b != find(bob[i], bob)) {
            free(bob);
            free(alice);
            return -1;
        }
    }

    free(bob);
    free(alice);
    return ans;
}

