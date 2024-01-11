struct Node *clone_runner(struct Node *s, struct Node **h)
{
    // Check whether the node is cloned
    if (h[s->val])
        return  h[s->val];

    // Clone new node
    struct Node *obj = malloc(sizeof(struct Node));
    obj->val = s->val;
    obj->numNeighbors = s->numNeighbors;
    obj->neighbors = calloc(obj->numNeighbors, sizeof(struct Node*));
    // Add to hash
    h[obj->val] = obj;
    // DFS traverse neighbors
    for (int i = 0; i < obj->numNeighbors; i++) {
        struct Node *cur_neighbor = s->neighbors[i];
        obj->neighbors[i] = clone_runner(cur_neighbor, h);
    }

    return obj;
}

struct Node *cloneGraph(struct Node *s)
{
    if (!s)
        return NULL;

    // Trick: Due to the condition "1 <= Node.val <= 100," simply create a hashset for values from 1 to 100.
    struct Node *hash[101] = {0};
    return clone_runner(s, hash);
}
