int findCenter(int** edges, int edgesSize, int* edgesColSize)
{
    if ((edges[0][0] != edges[1][0]) && (edges[0][0] != edges[1][1]))
        return edges[0][1];
    return edges[0][0];
}
