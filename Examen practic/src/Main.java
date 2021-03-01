import java.util.Arrays;
import java.util.Queue;
import java.util.Random;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        final int nrRanduri = 10;
        final int nrLocuri = 10;

        // interval in ms pentru afisarea locurilor
        final long T = 1000;

        SalaSpectacol salaSpectacol = new SalaSpectacol(nrRanduri, nrLocuri);

        Random r = new Random();
        Message[] messages = new Message[100];

        for (int i = 0; i < messages.length; i++) {
            messages[i] = new Message(r.nextInt(nrRanduri), r.nextInt(nrLocuri));
        }

        // structuri necesare implementarii sablonului producator-consumator
        Lock lock = new ReentrantLock();
        Condition alreadyTaken = lock.newCondition();
        Queue<Message> messageQueue = new LinkedBlockingQueue<>();
        AtomicBoolean done = new AtomicBoolean();
        AtomicBoolean shouldStop = new AtomicBoolean();

        Thread p1 = new Producer(salaSpectacol, lock, alreadyTaken, Arrays.copyOf(messages, 50), messageQueue, done);
        p1.start();
        Thread p2 = new Producer(salaSpectacol, lock, alreadyTaken, Arrays.copyOfRange(messages, 50, 99), messageQueue, done);

        Thread c1 = new Consumer(salaSpectacol, lock, alreadyTaken, messageQueue, done);
        c1.start();

        Thread m1 = new SpectacleIterator(salaSpectacol, T, shouldStop);
        m1.start();

        p1.join();
        p2.join();
        done.set(true);
        c1.join();
        System.out.println("am oprit consumatorul");
        shouldStop.set(true);
        m1.join();
    }
}
