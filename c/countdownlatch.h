#include <stdint.h>
#include <pthread.h>

struct countdown_latch {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    uint64_t count;
};

typedef struct countdown_latch countdown_latch;

void countdown_latch_init(countdown_latch *latch, uint64_t value);
void countdown_latch_await_latch(countdown_latch *latch);
void countdown_latch_countdown(countdown_latch *latch);
