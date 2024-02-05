static int set_find(int *set, int target)
{
    if (set[target] == target)
        return target;

    int ret = set_find(set, set[target]);
    set[target] = ret;
    return ret;
}

static void set_union(int *set, int x, int y)
{
    x = set_find(set, x);
    set[x] = set_find(set, y);
}

int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize)
{
   int *set = malloc(sizeof(int)*(edgesSize + 1));
   for (int i = 1; i <= edgesSize; i++)
      set[i] = i;

   int *ret = malloc(sizeof(int)*2);
   *returnSize = 2;
   for (int i = 0; i < edgesSize; i++) {
      // detect the cycle
      if (set_find(set, edges[i][0]) == set_find(set, edges[i][1])) {
         ret[0] = edges[i][0];
         ret[1] = edges[i][1];
         break;
      }
      set_union(set, edges[i][0], edges[i][1]);
   }

   free(set);
   return ret;
}
