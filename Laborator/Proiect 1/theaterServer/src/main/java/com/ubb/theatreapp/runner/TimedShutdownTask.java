package com.ubb.theatreapp.runner;

import java.util.TimerTask;

public class TimedShutdownTask extends TimerTask {

    @Override
    public void run() {
        System.exit(0);
    }
}
