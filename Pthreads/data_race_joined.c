#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4

void *hello (void *pArgs){
	int *p = (int*)pArgs;
	int myNum = *p;
	printf("Hello Thread %d\n", myNum);
	return 0;
}

int main (void) {
	int i;
	pthread_t tid[NUM_THREADS];
	//data race
	for (i = 0; i<NUM_THREADS; i++) {
		pthread_create (&tid[i], NULL, hello, &i);
	}

	//correcting data_race
	//for (i = 0; i<NUM_THREADS; i++){
	//	tNum[i] = i;
	//	pthread_create(&tid[i], NULL, hello, &tNum[i]);
	//}

	for (i = 0; i< NUM_THREADS;i++){
		pthread_join(tid[i], NULL);
	}

	return 0;
}
