typedef struct __data {
    int x;
    int y;
    int step;
} data_t;

typedef struct __list_node {
    data_t pos;
    struct __list_node *next;
} node_t;

typedef struct {
    node_t *head;
    node_t *tail;
    int size;
} q_list_t;

static inline q_list_t *q_create()
{
    q_list_t *obj = malloc(sizeof(q_list_t));
    obj->head = obj->tail = NULL;
    obj->size = 0;
    return obj;
}

static inline bool q_is_empty(q_list_t *obj)
{
    return (0 == obj->size);
}

static void q_push(q_list_t *obj, int row, int col, int step)
{
    node_t *newl = malloc(sizeof(node_t));
    newl->pos.x = row;
    newl->pos.y = col;
    newl->pos.step = step;
    newl->next = NULL;
    if (q_is_empty(obj))
        obj->head = newl;
    else
        obj->tail->next = newl;

    obj->tail = newl;
    obj->size += 1;
}

static data_t q_pop(q_list_t *obj)
{
    data_t ret = obj->head->pos;
    node_t *del = obj->head;
    obj->head = del->next;
    free(del);
    obj->size -= 1;
    return ret;
}

static inline void q_release(q_list_t *obj)
{
    node_t *cur = obj->head;
    while (cur) {
        node_t *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    free(obj);
}

static inline int adjust_target(int x)
{
    return abs(x) + 2;
}

int minKnightMoves(int x, int y)
{
    /**
     *  - We start the position from <2, 2> to avoid shift 2 unit to
     *    left or top int the begining.
     *  - Force the target <x,y> to positive and make a 2 unit offset
     */
    x = adjust_target(x);
    y = adjust_target(y);
    int ret = 0, max_r = x + 3, max_c = y + 3;
    q_list_t *q = q_create();
    char **chk = malloc(sizeof(char *) * max_r);
    for (int i = 0; i < max_r; i++)
        chk[i] = calloc(max_c, sizeof(char));

    int dir[8][2] = {{2, 1}, {-2, 1}, {2, -1}, {-2, -1},
                     {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};
    /* Put the start node <2, 2> */
    q_push(q, 2, 2, ret);
    chk[2][2] = 1;
    while (!q_is_empty(q)) {
        data_t cur_pos = q_pop(q);
        if (cur_pos.x == x && cur_pos.y == y) {
            ret = cur_pos.step;
            break;
        }
        /* tolerance of the starting boundary */
        int range_row_h = cur_pos.x - 2, range_col_h = cur_pos.y - 2;
        for (int i = 0; i < 8; i++) {
            int test_x = cur_pos.x + dir[i][0], test_y = cur_pos.y + dir[i][1];
            if (test_x >= 0 && test_x >= range_row_h && test_x < max_r &&
                test_y >= 0 && test_y >= range_col_h && test_y < max_c &&
                chk[test_x][test_y] == 0) {
                q_push(q, test_x, test_y, cur_pos.step + 1);
                chk[test_x][test_y] = 1;
            }
        }
    }

    /* release allocated obj */
    for (int i = 0; i < max_r; i++)
        free(chk[i]);
    free(chk);
    q_release(q);

    return ret;
}