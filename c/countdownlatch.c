#include "countdownlatch.h"
#include <pthread.h>
#include <stdint.h>

void countdown_latch_init(countdown_latch *latch, uint64_t value) {
	pthread_mutex_init(&latch->mutex, NULL);
	pthread_cond_init(&latch->cond, NULL);
	latch->count = value;
	return;
}

void countdown_latch_await_latch(countdown_latch *latch) {
	pthread_mutex_lock(&latch->mutex);
	while (latch->count > 0) {
		pthread_cond_wait(&latch->cond, &latch->mutex);
	}
	pthread_mutex_unlock(&latch->mutex);
}

void countdown_latch_countdown(countdown_latch *latch) {
	pthread_mutex_lock(&latch->mutex);

	latch->count -= 1;
	if (latch->count <= 0) {
		latch->count = 0;	
		pthread_mutex_unlock(&latch->mutex);
		pthread_cond_broadcast(&latch->cond);
	} else {
		pthread_mutex_unlock(&latch->mutex);
	}
}
