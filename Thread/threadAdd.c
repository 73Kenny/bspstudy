#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep()
#include <pthread.h>

int a = 0;

void add(char* threadName)
{
	a++;
	printf("%s: a=%d\n", threadName, a);
	// sleep(1);
}

int main()
{
	pthread_t id1, id2;
	int i, ret;

	ret = pthread_create(&id1, NULL, (void*)add, "thread1");
	ret = pthread_create(&id2, NULL, (void*)add, "therad2");

	if (0 != ret)
	{
		printf("Create ptherad error!\n");
		exit(1);
	}

	pthread_join(id1, NULL);
	pthread_join(id2, NULL);

	return 0;
}
