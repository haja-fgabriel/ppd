import java.util.concurrent.atomic.AtomicBoolean;

public class SpectacleIterator extends Thread {
    private SalaSpectacol salaSpectacol;
    private final long T;
    private AtomicBoolean shouldStop;

    public SpectacleIterator(SalaSpectacol salaSpectacol, long t, AtomicBoolean shouldStop) {
        this.salaSpectacol = salaSpectacol;
        T = t;
        this.shouldStop = shouldStop;
    }

    @Override
    public void run() {
        super.run();
        while (!shouldStop.get()) {
            salaSpectacol.iterare();
            try {
                Thread.sleep(T);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
