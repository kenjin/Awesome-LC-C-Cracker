/***
Approach: Greedy

1. General Case
(Count of tasks with the maximum frequency - 1) x (n + 1) + (Number of tasks with the maximum frequency)
=> e.g. tasks = ["A","A","A","A","B","B","B","B","C","D"], n = 3

        [A, B, C] - [A, B, D] - [A, B, NULL] - [A, B]
        <-----------  3 groups  ----------->
        => max:  tasks with the maximum frequency (A = 4, B = 4)
        => max_task_ctr = total count of same max_repeated_task (A and B are both "4")
        => return (max - 1) * (n + 1) + max_task_ctr

2. If the total time required for tasks exceeds the minimum interval calculated above, the answer is the total time required for tasks.
=> e.g. tasks = ["A", "A", "A", "B", "B", "C", "C", "D", "D"], n = 2

***/

int leastInterval(char* tasks, int tasksSize, int n) {
    int ret = 0, max = 0, max_task_ctr = 0;
    int task_ctr[26] = {0};

    for (int i = 0; i < tasksSize; i++)
        task_ctr[(tasks[i] - 'A')] += 1;

    for (int i = 0; i < 26; i++) {
        if (task_ctr[i] > max) {
            max_task_ctr = 1;
            max = task_ctr[i];
        } else if (task_ctr[i] == max) {
            max_task_ctr++;
        }
    }

    ret = (max - 1) * (n + 1) + max_task_ctr;
    return (ret > tasksSize ? ret : tasksSize);
}
