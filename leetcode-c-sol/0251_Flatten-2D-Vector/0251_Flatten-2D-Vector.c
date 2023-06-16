/**

251. Flatten 2D Vector [M]
Ref: https://leetcode.com/problems/flatten-2d-vector/

esign and implement an iterator to flatten a 2d vector. It should support the following operations: next and hasNext.

 

Example:

Vector2D iterator = new Vector2D([[1,2],[3],[4]]);

iterator.next(); // return 1
iterator.next(); // return 2
iterator.next(); // return 3
iterator.hasNext(); // return true
iterator.hasNext(); // return true
iterator.next(); // return 4
iterator.hasNext(); // return false
 

Notes:

Please remember to RESET your class variables declared in Vector2D, as static/class variables are persisted across multiple test cases. Please see here for more details.
You may assume that next() call will always be valid, that is, there will be at least a next element in the 2d vector when next() is called.
 

Follow up:

As an added challenge, try to code it using only iterators in C++ or iterators in Java.

 */

typedef struct 
{
	int cur;
	int size;
	int *arr;    
} Vector2D;


Vector2D* vector2DCreate(int** v, int vSize, int* vColSize) 
{
	Vector2D *obj = malloc(sizeof(Vector2D));
	obj->arr = malloc(sizeof(int));
	obj->size = 0;
	for (int i = 0; i < vSize; i++)
	{
		/* Check [NULL] case */
		if (vColSize[i] == 0)
		{
			continue;
		}
		obj->arr = realloc(obj->arr, sizeof(int)*(obj->size+vColSize[i]));
		memcpy(&(obj->arr[obj->size]), v[i], sizeof(int)*(vColSize[i]));        
		obj->size += vColSize[i];
	}
	obj->cur = 0;
	return obj;
}

int vector2DNext(Vector2D* obj) 
{
	obj->cur += 1;
	return obj->arr[obj->cur-1];
}

bool vector2DHasNext(Vector2D* obj) 
{
	return (obj->cur < obj->size ? true : false);        
}

void vector2DFree(Vector2D* obj) 
{
	free(obj->arr);
	free(obj);
}

/**
 * Your Vector2D struct will be instantiated and called as such:
 * Vector2D* obj = vector2DCreate(v, vSize, vColSize);
 * int param_1 = vector2DNext(obj);

 * bool param_2 = vector2DHasNext(obj);

 * vector2DFree(obj);
 */
