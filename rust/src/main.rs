use std::num::Saturating;
use std::{env, thread};
use std::time::{SystemTime, UNIX_EPOCH};

fn main() {
    let args: Vec<String> = env::args().collect();
    let thread_count: i32 = args[1].parse().unwrap();


    for _ in 0::thread_count {

        thread::spawn(|| {
            
            let start = SystemTime::now();
            let current_time = start
                .duration_since(UNIX_EPOCH)
                .unwrap();

            busy_work(current_time.as_millis())

        })


    }
    
}

fn busy_work(started_time: u128, wait_milis : u128) {
    loop {


        let now = SystemTime::now()
            .duration_since(UNIX_EPOCH).unwrap()
            .as_millis();

        let time_passed = now - started_time;

        if time_passed >= wait_milis  {
            break;
        }

    }
}




