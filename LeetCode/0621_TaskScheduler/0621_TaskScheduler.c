/**
	Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different 
	letters represent different tasks. Tasks could be done without original order. Each task could be done 
	in one interval. For each interval, CPU could finish one task or just be idle.
	However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.
	You need to return the least number of intervals the CPU will take to finish all the given tasks.

	Example:
	Input: tasks = ["A","A","A","B","B","B"], n = 2
	Output: 8
	Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.

 */
#define  MAX(a ,b)  (a > b ? a : b)
int leastInterval(char* tasks, int tasksSize, int n) {
	/**
	Input: tasks = ["A","A","A","A","B","B","B","B","C","D"], n = 3

	(1) General Case
		[A, B, C] - [A, B, D] - [A, B, NULL] - [A, B]
		<-----------  3 groups  ----------->
		=> group_count = max_repeated_task - 1 (EX: A = 4-1)
		=> remaining_tasks = total count of same max_repeated_task  (EX: A and B are both "4")            
		return Ans = (group_count)*n + remaining_tasks

	(2) Special Case
		if (tasksSize > Ans) return tasksSize

	*/
	int ret = 0, max = 0, remain = 0;
	int taskCtr[26];

	memset(taskCtr, 0, sizeof(int)*26);
	for (int i = 0; i < tasksSize; i++)
	{
		taskCtr[(tasks[i]-'A')] += 1;
	}

	for (int i = 0; i < 26; i++)
	{
		if (taskCtr[i] > max)
		{
			max = taskCtr[i];
		}
	}

	for (int i = 0; i < 26; i++)
	{
		if (taskCtr[i] == max)
		{
			max = taskCtr[i];
			remain++;
		}
	}

	ret = (max-1)*(n+1) + remain;
	return MAX(ret, tasksSize);
}
