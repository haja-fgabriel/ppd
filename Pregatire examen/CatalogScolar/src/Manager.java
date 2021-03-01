import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;

public class Manager extends Thread {
    private Condition areMedieSub5;
    private Lock lock;
    private final Catalog catalog;

    public Manager(Condition areMedieSub5, Lock lock, Catalog catalog) {
        this.areMedieSub5 = areMedieSub5;
        this.lock = lock;
        this.catalog = catalog;
    }

    @Override
    public void run() {
        super.run();

        while (!FinishedStatus.getInstance().isFinished()) {
            //System.out.println("Runnin");
            try {
                lock.lock();
                areMedieSub5.await();
                lock.unlock();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Studenti cu medii sub 5:");
            //synchronized (catalog) {
                //catalog.getAll().stream().filter(c -> c.getMedia() < 5).forEach(System.out::println);
            //}
        }
    }
}
