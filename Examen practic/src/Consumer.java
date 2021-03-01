import java.util.NoSuchElementException;
import java.util.Queue;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.logging.Logger;

public class Consumer extends Thread {
    private final static Logger logger = Logger.getLogger(Consumer.class.getName());
    private SalaSpectacol salaSpectacol;
    private Lock lock;
    private Condition alreadyTaken;
    private Queue<Message> messageQueue;
    private AtomicBoolean done;

    public Consumer(SalaSpectacol salaSpectacol, Lock lock, Condition alreadyTaken, Queue<Message> messageQueue, AtomicBoolean done) {
        this.salaSpectacol = salaSpectacol;
        this.lock = lock;
        this.alreadyTaken = alreadyTaken;
        this.messageQueue = messageQueue;
        this.done = done;
    }

    @Override
    public void run() {
        super.run();
        while (!done.get()) {
            if (!done.get()) {
                logger.info("Waiting for producers");
                try {
                    lock.lock();
                    alreadyTaken.await();
                    lock.unlock();
                    Message m = messageQueue.remove();
                    logger.warning("Loc deja ocupat la randul " + m.getRand() + ", locul " + m.getLoc());
                } catch (NoSuchElementException e) {
                    logger.info("Nu mai avem locuri de pus");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                } finally {
                    lock.unlock();
                }

            }
        }
    }
}
