const { parentPort } = require('worker_threads');

parentPort.on('message', (msg) => {
    switch (msg) {
        case 'START':
            busyWork();
            process.exit();
            break;
    }
});

function busyWork() {
    var start = Date.now();
    var arr = [1, 2];
    var aux;
    var loops = 0;
    while(true) {
        loops++;
        aux = arr[1];
        arr[1] = arr[2];
        arr[2] = aux;

        var elapse = Date.now() - start;
        if (elapse <= 0) elapse = 1;
        if (elapse > 5000) {
            break;
        }
    }
}

