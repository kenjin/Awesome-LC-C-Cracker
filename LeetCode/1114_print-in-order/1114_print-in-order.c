typedef struct 
{
	// User defined data may be declared here.
	pthread_mutex_t mutex;
	int done1;
	int done2;
	pthread_cond_t firstCond;
	pthread_cond_t secondCond;
} Foo;

Foo* fooCreate() {
	Foo* obj = (Foo*) malloc(sizeof(Foo));

	// Initialize user defined data here.
	pthread_mutex_init(&obj->mutex,NULL);
	pthread_cond_init(&obj->firstCond,NULL);
	pthread_cond_init(&obj->secondCond,NULL);
	obj->done1 = 0;
	obj->done2 = 0;
	return obj;
}

void first(Foo* obj) 
{
	// printFirst() outputs "first". Do not change or remove this line.
	pthread_mutex_lock(&obj->mutex);
	printFirst();
	obj->done1 = 1;
	pthread_mutex_unlock(&obj->mutex);
	pthread_cond_signal(&obj->firstCond);
}

void second(Foo* obj) 
{

	// printSecond() outputs "second". Do not change or remove this line.
	pthread_mutex_lock(&obj->mutex);
	while (!obj->done1)
	{
		pthread_cond_wait(&obj->firstCond, &obj->mutex);
	}
	printSecond();
	obj->done2 = 1;
	pthread_mutex_unlock(&obj->mutex);
	pthread_cond_signal(&obj->secondCond);
}

void third(Foo* obj) 
{
	// printThird() outputs "third". Do not change or remove this line.
	pthread_mutex_lock(&obj->mutex);
	while (!obj->done2)
	{
		pthread_cond_wait(&obj->secondCond, &obj->mutex);
	}
	printThird();
	pthread_mutex_unlock(&obj->mutex);
}

void fooFree(Foo* obj) {
	// User defined data may be cleaned up here.
	pthread_mutex_destroy(&obj->mutex);
	pthread_cond_destroy(&obj->secondCond);
	pthread_cond_destroy(&obj->firstCond);
	free(obj);
}
