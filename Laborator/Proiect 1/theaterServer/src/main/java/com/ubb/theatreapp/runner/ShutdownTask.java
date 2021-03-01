package com.ubb.theatreapp.runner;

import java.util.Timer;

public class ShutdownTask implements Task {
    private long timeout;

    public ShutdownTask(long timeout) {
        this.timeout = timeout;
    }

    @Override
    public Object call() throws Exception {
        Timer t = new Timer();
        t.schedule(new TimedShutdownTask(), timeout);

        return null;
    }
}
