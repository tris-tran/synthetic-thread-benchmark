use std::{env, thread, i32};
use std::time::{SystemTime, UNIX_EPOCH};
use std::sync::Arc;

mod concurrent;

fn main() {
    let args: Vec<String> = env::args().collect();
    let thread_count: u32 = args[1].parse().unwrap();

    let latch = Arc::new(concurrent::CountdownLatch::new(1));
    let finishing_latch = Arc::new(concurrent::CountdownLatch::new(thread_count));

    for _ in 0..thread_count {
        let latch_inned = latch.clone();
        let finishing_inner_latch = finishing_latch.clone();

        thread::spawn(move|| {
            let starting_latch = &*latch_inned;
            let finishing_inner_latch = &*finishing_inner_latch;

            starting_latch.await_latch();

            let current_time = SystemTime::now()
                .duration_since(UNIX_EPOCH)
                .unwrap()
                .as_millis();

            busy_work(current_time, 10000);

            finishing_inner_latch.countdown();
        });
    }

    let starting_latch = &*latch;
    starting_latch.countdown();

    finishing_latch.await_latch();
}

fn busy_work(started_time: u128, wait_milis : u128) {
    let mut aux : i32;
    let mut data: [i32; 2] = [0, 1];
    loop {
        aux = data[0];
        data[0] = data[1];
        data[1] = aux;

        let now = SystemTime::now()
            .duration_since(UNIX_EPOCH).unwrap()
            .as_millis();

        let time_passed = now - started_time;

        if time_passed >= wait_milis  {
            break;
        }
    }
}




