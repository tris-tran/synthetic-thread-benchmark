use std::sync::{Mutex, Condvar};

pub struct CountdownLatch {
    mutex: Mutex<u32>,
    cvar: Condvar,
}

impl CountdownLatch {
    pub fn new(count: u32) -> CountdownLatch {
        return CountdownLatch {
            mutex : Mutex::new(count),
            cvar : Condvar::new()
        };
    }

    pub fn await_latch(&self) {
        let mut count = self.mutex.lock().unwrap();
        while *count > 0 {
            count = self.cvar.wait(count).unwrap();
        }
    }

    pub fn countdown(&self) {
        let mut count = self.mutex.lock().ok().unwrap();
        *count -= 1;
        self.cvar.notify_all();
    }
}


