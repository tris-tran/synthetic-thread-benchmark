#include"countdownlatch.h"
#include<bits/pthreadtypes.h>
#include<stdio.h>
#include<time.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void busy_work(long started_time, long wait_milis);
void *thread_work(void *param);

struct latches {
	countdown_latch init_latch;
	countdown_latch finished_latch;
};


int main(int argc, char **argv) {

	int threads = atoi(argv[1]);
	struct latches latch;

	// We can setup the stack size
	// pthread_attr_setstacksize(3)
	//

	countdown_latch_init(&latch.init_latch, 1);
	countdown_latch_init(&latch.finished_latch, threads);

	for (int i=0; i<threads; i++) {
		pthread_t thread_t;
		pthread_create(&thread_t, NULL, &thread_work, &latch);
	}

	printf("All threads waiting run\n");
	fflush(stdout);
	getchar();

	printf("Running threads\n");
	countdown_latch_countdown(&latch.init_latch);

	countdown_latch_await_latch(&latch.finished_latch);
	return 0;
}

void *thread_work(void *params) {
	struct latches* latch = params;

	countdown_latch_await_latch(&latch->init_latch);

	long start = clock();
	busy_work(start, 10000);

	countdown_latch_countdown(&latch->finished_latch);
	return 0;
}

void busy_work(long started_time, long wait_milis) {
	int work[2] = {0, 1};
	int aux;
	while(1) {
		for (int i=0; i<10000; i++) {
			aux = work[0];
			work[0] = work[1];
			work[1] = aux;
		}
		
		long elapse = clock() - started_time;
		if (elapse >= wait_milis) {
			break;
		}
	}
}
