#include"countdownlatch.h"
#include<bits/pthreadtypes.h>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void busy_work();
void *thread_work(void *param);

struct latches {
	countdown_latch init_latch;
	countdown_latch finished_latch;
};

int main(int argc, char **argv) {

	int threads = atoi(argv[1]);
	struct latches latch;

	countdown_latch_init(&latch.init_latch, 1);
	countdown_latch_init(&latch.finished_latch, threads);

	for (int i=0; i<threads; i++) {
		pthread_t thread_t;
		pthread_attr_t attr;
		pthread_attr_setstacksize(&attr, 16384);
		pthread_attr_init(&attr);
		pthread_create(&thread_t, &attr, &thread_work, &latch);
	}

	printf("All threads waiting run\n");
	fflush(stdout);
	getchar();

	countdown_latch_countdown(&latch.init_latch);

	countdown_latch_await_latch(&latch.finished_latch);
	return 0;
}

void *thread_work(void *params) {
	struct latches* latch = params;
	countdown_latch_await_latch(&latch->init_latch);
	busy_work();
	countdown_latch_countdown(&latch->finished_latch);
	return 0;
}

//We are not suppose to optimize the busywork
#pragma optimize("", off)
void busy_work() {
	int work[2] = {0, 1};
	int aux;
	for (int i=0; i<10000; i++) {
		aux = work[0];
		work[0] = work[1];
		work[1] = aux;
		aux = work[0] * work[1];
	}
}
#pragma optimize("", on)
