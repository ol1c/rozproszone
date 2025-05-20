public class Main {
    public static void main(String[] args) throws InterruptedException {
        final BinarySemaphore sem = new BinarySemaphore(true);
        final int[] n = {0};
        Runnable task = () -> {
            String name = Thread.currentThread().getName();
            try {
                int tmp;
                System.out.println(name + " started");
                for (int i = 0; i < 50; i++) {
                    // if the marked lines are deleted:
                    // threads may interfere with each other and the final result will be incorrect
                    sem.acquire(); // line 1
                    tmp = n[0];
                    tmp += 1;
                    n[0] = tmp;
                    sem.release(); // line 2
                    Thread.sleep(50);
                }
                System.out.println(name + " finished");
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        };

        System.out.println("n = " + n[0]);
        Thread t1 = new Thread(task, "Thread 1");
        Thread t2 = new Thread(task, "Thread 2");
        t1.start();
        t2.start();
        t1.join();
        t2.join();

        System.out.println("n = " + n[0]);
    }
}