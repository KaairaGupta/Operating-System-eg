#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int shared;
int readers = 0;
int w = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;    /* mutex lock for buffer*/
pthread_cond_t c_reader = PTHREAD_COND_INITIALIZER; /* reader waits on this cond var */
pthread_cond_t c_writer = PTHREAD_COND_INITIALIZER; /* writer waits on this cond var */

void *writer (void *param);
void *reader (void *param);

int main(int argc, char *argv[]) {

	pthread_t r[5];
	pthread_t w[5];
	int i;

	for (i = 0; i<5; i++) {
		pthread_create(&r[i], NULL, reader, NULL);
		pthread_create(&w[i], NULL, writer, NULL);
	}



	for (i = 0; i<5; i++) {
                pthread_join(r[i], NULL);
                pthread_join(w[i], NULL);
        }

	return 0;
}

void *writer(void *param) {
		int i;
		int r = -1;
		for (i=1; i<=10; i++) {
			usleep(2000);

			pthread_mutex_lock (&m);
			while (readers !=0){
				pthread_cond_wait(&c_writer, &m);
			}

			shared = i;
			w = -1;
			r = readers;
			pthread_mutex_unlock(&m);
			fprintf(stdout, "writer --> shared: %d, reader: %d\n", shared, r);

			pthread_mutex_lock(&m);
			w=0;
			pthread_mutex_unlock(&m);
			pthread_cond_broadcast(&c_reader);
			pthread_cond_signal(&c_writer);
			
			
		}
	pthread_exit(0);
	
}

void *reader(void *param) {
	int i;
	int r = 0;
	for (i = 0; i <10; i++){
		usleep(2000);
		pthread_mutex_lock(&m);
		while ( w == -1){
			pthread_cond_wait(&c_reader,&m);
		}
		readers++;
		r = readers;
		pthread_mutex_unlock(&m);

		fprintf(stdout, "reader --> shared: %d, reader: %d\n", shared, r);
		pthread_mutex_lock(&m);
		readers --;
		pthread_mutex_unlock(&m);
		if(readers == 0){
			pthread_cond_broadcast(&c_writer);
		}
	}

	pthread_exit(0);

}
