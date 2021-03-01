public class FinishedStatus {
    private boolean finished;

    private static FinishedStatus instance;

    private FinishedStatus() {
        finished = false;
    }

    public static FinishedStatus getInstance() {
        if (instance == null) {
            instance = new FinishedStatus();
        }
        return instance;
    }

    public boolean isFinished() {
        return finished;
    }

    public void setFinished(boolean finished) {
        this.finished = finished;
    }
}
