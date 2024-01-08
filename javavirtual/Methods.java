public class Methods {

	public static int getNumberOfThreads(String[] args) {
		return Integer.valueOf(args[0]);
	}

	public static void busyWork() {
		int work[] = { 1, 2 };
		int aux;
		for (int i = 0; i < 10_000; i++) {
			aux = work[0];
			work[0] = work[1];
			work[1] = aux;

			aux = work[0] * work[1];
		}
	}
}
