
bool isRectangleOverlap(int* rec1, int rec1Size, int* rec2, int rec2Size)
{
	bool x = false, y = false;
	// Check X
	if ((rec1[0] > rec2[0] && rec1[0] < rec2[2]) ||
			(rec1[2] > rec2[0] && rec1[2] < rec2[2]) ||
			(rec2[0] > rec1[0] && rec2[0] < rec1[2]) ||
			(rec2[2] > rec1[0] && rec2[2] < rec1[2]))
	{
		x = true;        
	}
	// Check Y
	if ((rec1[1] > rec2[1] && rec1[1] < rec2[3]) ||
			(rec1[3] > rec2[1] && rec1[3] < rec2[3]) ||
			(rec2[1] > rec1[1] && rec2[1] < rec1[3]) ||
			(rec2[3] > rec1[1] && rec2[3] < rec1[3]))
	{
		y = true;        
	}
	return x & y;
}


