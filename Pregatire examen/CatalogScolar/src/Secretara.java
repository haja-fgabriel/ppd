import java.util.List;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Secretara extends Thread {
    private final Catalog catalog;
    private Condition areMedieSub5;
    private Cursant[] cursanti;
    private Lock lock;
    private int start;
    private int end;

    public Secretara(Catalog catalog, Condition areMedieSub5, Lock lock, Cursant[] cursanti, int start, int end) {
        this.catalog = catalog;
        this.areMedieSub5 = areMedieSub5;
        this.lock = lock;
        this.cursanti = cursanti;
        this.start = start;
        this.end = end;
    }

    @Override
    public void run() {
        super.run();
        for (int i = start; i < end; i++) {
            System.out.println(i);
            catalog.addCursant(cursanti[i]);
            if (cursanti[i].getMedia() < 5) {
                lock.lock();
                areMedieSub5.signal();
                lock.unlock();
            }
            try {
                Thread.sleep(20);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        lock.lock();
        areMedieSub5.signal();
        lock.unlock();
    }
}
