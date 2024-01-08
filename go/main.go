package main

import (
	"fmt"
	"os"
	"strconv"
	"sync"
)

func main() {

    threadCount, _ := strconv.Atoi(os.Args[1])

    fmt.Println(threadCount)

    var waitLatch sync.WaitGroup
    var waitGroup sync.WaitGroup

    waitLatch.Add(1)

    for i := 0; i < threadCount; i++ {
        waitGroup.Add(1)
        go func() {
            defer waitGroup.Done()
            waitLatch.Wait()
            busyWork()
        }()
    }

    var ignore string
    fmt.Println("All threads waiting run")
    fmt.Scanln(&ignore)

    waitLatch.Done();

    waitGroup.Wait();
}


func busyWork() {
    aux := 0;
    work := [2]int{1, 2}
    for i := 0; i < 10000; i++ {
        aux = work[0]
        work[0] = work[1]
        work[1] = aux

        aux = work[0] * work[1]
    }
}
