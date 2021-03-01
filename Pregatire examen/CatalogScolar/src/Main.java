import java.util.Random;
import java.util.concurrent.locks.*;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        final int n = 5;

        Lock lock = new ReentrantLock();
        Condition areMedieSub5 = lock.newCondition();
        Catalog catalog = new Catalog();
        Random random = new Random();
        Cursant cursanti[] = new Cursant[100];

        for (int i = 0; i < 100; i++) {
            cursanti[i] = new Cursant(i, random.nextFloat() * 9 + 1);
        }

        int start = 0;
        int end;
        int chunk = 100 / n;
        int rest = 100 % n;

        Thread[] secretare = new Secretara[n];

        for (int i = 0; i < n; i++) {
            end = start+chunk;
            if (rest > 0) {
                end++;
                rest--;
            }

            secretare[i] = new Secretara(catalog, areMedieSub5, lock, cursanti, start, end);
            secretare[i].start();

            start = end;
        }

        Thread manager = new Manager(areMedieSub5, lock, catalog);
        manager.start();

        for (int i = 0; i < n; i++) {
            secretare[i].join();
        }

        //manager.interrupt();
        manager.join();
    }
}
