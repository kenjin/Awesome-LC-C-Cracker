static inline bool validate(int** m1, int** m2, int m_sz) {
    for (int x = 0; x < m_sz; x++) {
        for (int y = 0; y < m_sz; y++) {
            if (m1[x][y] != m2[x][y])
                return false;
        }
    }
    return true;
}

bool findRotation(int** mat, int matSize, int* matColSize, int** target,
                  int targetSize, int* targetColSize) {
    // no roatation
    if (validate(mat, target, matSize))
        return true;

    // try to rotate three times
    for (int r_ctr = 0; r_ctr < 3; r_ctr++) {
        int half_sz = (matSize >> 1);
        for (int x = 0; x < half_sz; x++) {
            for (int y = x; y < matSize - 1 - x; y++) {
                int tmp = mat[x][y];
                int rotate_x = matSize - 1 - x;
                int rotate_y = matSize - 1 - y;
                mat[x][y] = mat[rotate_y][x];
                mat[rotate_y][x] = mat[rotate_x][rotate_y];
                mat[rotate_x][rotate_y] = mat[y][rotate_x];
                mat[y][rotate_x] = tmp;
            }
        }
        if (validate(mat, target, matSize))
            return true;
    }
    return false;
}
