
int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize)
{
	int head = gasSize-1, tail = gasSize-1;
	int tank = gas[head] - cost[head];
	while ((head+gasSize-1)%gasSize != tail)
	{
		if (tank < 0)
		{            
			head = (head+gasSize-1)%gasSize;
			tank += gas[head] - cost[head];
		} else
		{
			tail = (tail+1)%gasSize;
			tank += gas[tail] - cost[tail];            
		}
	}

	return (tank >= 0 ? head : -1);
}

