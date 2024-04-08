/***

First, calculate the number of students in students[](c_prefer and s_prefer) who
prefer circular and square sandwiches.Continuously iterate over the top of the
sandwiches[]. As long as there are students with this preference (e.g.
circular), decrement the corresponding preference count (e.g. c_prefer) in
students[] and pop the sandwich top. Continue until the current top sandwich has
no corresponding demand(e.g. c_prefer is 0 but sandwiches[0] = 1) or the
sandwich stack is empty. The remaining number of elements in the stack
represents the number of students who cannot eat a sandwich.

***/

int countStudents(int* students, int studentsSize, int* sandwiches,
                  int sandwichesSize) {
    int c_prefer = 0, s_prefer = 0, top = 0;
    for (int i = 0; i < studentsSize; i++) {
        if (students[i])
            c_prefer++;
        else
            s_prefer++;
    }

    while (top < sandwichesSize) {
        if (sandwiches[top] && c_prefer) {
            c_prefer--;
            top++;
        } else if (!sandwiches[top] && s_prefer) {
            s_prefer--;
            top++;
        } else {
            break;
        }
    }
    return sandwichesSize - top;
}
