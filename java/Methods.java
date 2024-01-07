
public class Methods {

	public static int getNumberOfThreads(String[] args) {
		return Integer.valueOf(args[0]);
	}

	public static void busyWork() {
		long initialTime = System.currentTimeMillis();
		int work[] = { 1, 2 };
		int aux;
		while (true) {
			aux = work[0];
			work[0] = work[1];
			work[1] = aux;

			long milisAfterWork = System.currentTimeMillis();
			if (milisAfterWork - initialTime>=10000) { break; }
		}
	}
}
