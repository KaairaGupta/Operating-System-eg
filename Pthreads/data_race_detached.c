#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4
#include <unistd.h>

void *hello (void *pArgs){
        int *p = (int*)pArgs;
        int myNum = *p;
        printf("Hello Thread %d\n", myNum);
        return 0;
}

int main (void) {
        int i;
        pthread_t tid[NUM_THREADS];

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
        //data race
        for (i = 0; i<NUM_THREADS; i++) {
                pthread_create (&tid[i], &attr, hello, &i);
        }

        sleep(3);

        return 0;
}

