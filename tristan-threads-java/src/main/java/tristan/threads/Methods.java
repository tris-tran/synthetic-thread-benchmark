package tristan.threads;

public class Methods {

	public static int getNumberOfThreads(String[] args) {
		return Integer.valueOf(args[0]);
	}

	public static void busyworkForMilis(final long initialTime, final long target, int[] work) {
		while (true) {
			int aux = work[0];
			work[0] = work[1];
			work[1] = aux;

			long milisAfterWork = System.currentTimeMillis();
			if (milisAfterWork - initialTime>=10000) { break; }
		}
	}
}
