use std::io::Write;
use std::{env, thread, io};
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

            busy_work();

            finishing_inner_latch.countdown();
        });
    }

    println!("All threads waiting run");
    let _ = io::stdout().flush();

    let mut buf = String::new();
    let _ = io::stdin().read_line(&mut buf);

    let starting_latch = &*latch;
    starting_latch.countdown();

    finishing_latch.await_latch();

}

fn busy_work() {
    let mut aux : i32;
    let mut data: [i32; 2] = [0, 1];
    for _ in 0..10000 {
        aux = data[0];
        data[0] = data[1];
        data[1] = aux;
        aux = data[0] * data[1];
    }
}




