

bool validMountainArray(int *A, int ASize)
{
    if (ASize <= 2 || A[1] < A[0])
        return false;

    bool dec = false;
    int prev = A[1];
    for (int i = 2; i < ASize; i++) {
        if (!dec) {
            if (A[i] == prev)
                return false;
            else if (A[i] < prev)
                dec = true;
        } else {
            if (A[i] >= prev)
                return false;
        }
        prev = A[i];
    }


    return (dec == true);
}
