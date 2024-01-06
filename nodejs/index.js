const { Worker } = require('worker_threads');
const readline = require('readline');
const {stdin: input, stdout: output} = require('process');

const threadCount = process.argv[2];

var workers = [];

for (let i = 0; i < threadCount; i++) {
    var worker = new Worker("./work.js");
    workers.push(worker);
}

var read = readline.createInterface({input, output});

read.question("All threads waiting run\n", (line) => {
    read.close();

    workers.forEach(element => {
        element.postMessage("START");
    });

    workers = [];
});
