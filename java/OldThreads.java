import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.Scanner;

public class OldThreads {
	public static void main(String[] args) throws InterruptedException {
		int threadCount = Methods.getNumberOfThreads(args);
		AtomicInteger atomicErrors = new AtomicInteger(1);

		CountDownLatch countDownLatch = new CountDownLatch(1);
		CountDownLatch allThreadsWait = new CountDownLatch(threadCount);

		ThreadFactory threadFactory = r -> {
			Thread thread = new Thread(r);
			thread.setDaemon(true);
			return thread;
		};

		for (int i = 0; i < threadCount; i++) {
			threadFactory.newThread(() -> {
				//We wait for all threads to start
				try {
					countDownLatch.await();
				} catch (InterruptedException e) {
					atomicErrors.addAndGet(1);
				}

				Methods.busyWork();

				//We finish working
				allThreadsWait.countDown();
			}).start();
		}

		var scanner = new Scanner(System.in);
		System.out.println("All threads created");
		var ignore = scanner.nextLine();
		//We allow all threasd to work all at once.
		countDownLatch.countDown();
		//We wait for all threads to finish
		allThreadsWait.await();
	}
}
