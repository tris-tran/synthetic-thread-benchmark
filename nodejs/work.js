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
    var arr = [1, 2];
    var aux;
    for (let i = 0; i < 10000; i++) {
        aux = arr[1];
        arr[1] = arr[2];
        arr[2] = aux;
        aux = arr[0] * arr[1];
    }
}

