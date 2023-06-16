#define MIN(a, b)   (a < b ? a : b)
#define MIN_UNUSED  INT_MAX

int minDominoRotations(int* A, int ASize, int* B, int BSize)
{
    if (ASize == 1)
    {
        return 0;
    }

    int sameCtrA = 0, sameCtrB = 0, min = MIN_UNUSED;
    int rotationA, rotationB;
    for (int i = 1; i < ASize; i++)
    {
        if (A[i] != A[0] && B[i] != A[0])
        {
            break;
        }
        if (A[i] == A[0])
        {
           sameCtrA++;
        }
        if (B[i] == A[0])
        {
           sameCtrB++; 
        }
        
        if (i == ASize-1)
        {
            rotationA = ASize - sameCtrA - 1;
            rotationB = ASize - sameCtrB;
            min = MIN(rotationA, rotationB);
        }
    }
    
    sameCtrA = 0, sameCtrB = 0;
    for (int i = 1; i < ASize; i++)
    {
        if (A[i] != B[0] && B[i] != B[0] && min == MIN_UNUSED)
        {
            break;
        }

        if (A[i] == B[0])
        {
           sameCtrA++; 
        }
        if (B[i] == B[0])
        {
           sameCtrB++; 
        }
        
        if (i == ASize-1)
        {
            rotationB = ASize - sameCtrB - 1;
            rotationA = ASize - sameCtrA;
            int tmpMin = MIN(rotationA, rotationB);
            return MIN(min, tmpMin);
        }
    }
    
    return -1;
}

