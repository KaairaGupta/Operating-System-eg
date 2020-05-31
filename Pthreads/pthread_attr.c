#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void *foo (void *arf) {
	printf("Foobar!\n");
	pthread_exit(NULL);
}

int main (void) {

	int i;
	pthread_t tid;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	pthread_create(&tid, &attr, foo, NULL);

	sleep(3);
	return 0;
}
