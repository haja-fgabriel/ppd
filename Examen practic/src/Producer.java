import java.util.Queue;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.logging.Logger;

public class Producer extends Thread {
    private final static Logger logger = Logger.getLogger(Producer.class.getName());
    private SalaSpectacol salaSpectacol;
    private Lock lock;
    private Condition condition;
    private Message[] messages;
    private Queue<Message> messageQueue;
    private AtomicBoolean done;

    public Producer(SalaSpectacol salaSpectacol, Lock lock, Condition condition, Message[] messages, Queue<Message> messageQueue, AtomicBoolean done) {
        this.salaSpectacol = salaSpectacol;
        this.lock = lock;
        this.condition = condition;
        this.messages = messages;
        this.messageQueue = messageQueue;
        this.done = done;
    }

    @Override
    public void run() {
        super.run();
        done.set(false);
        for (int i = 0; i < messages.length; i++) {
//            System.out.println(messages[i]);
            if (!salaSpectacol.adaugaLoc(messages[i].getRand(), messages[i].getLoc())) {
                lock.lock();
                messageQueue.add(messages[i]);
                condition.signal();
                lock.unlock();
            }
        }
        lock.lock();
        condition.signal();
        lock.unlock();
    }
}
