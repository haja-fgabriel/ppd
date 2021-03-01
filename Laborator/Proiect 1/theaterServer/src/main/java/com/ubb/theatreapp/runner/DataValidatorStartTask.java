package com.ubb.theatreapp.runner;

import com.ubb.theatreapp.service.SaleService;
import com.ubb.theatreapp.service.TheaterService;
import org.springframework.stereotype.Component;

import java.util.Timer;
import java.util.TimerTask;

public class DataValidatorStartTask implements Task {
    private final static long INTERVAL = 5000L;

    private TheaterService theaterService;

    public DataValidatorStartTask(TheaterService theaterService) {
        this.theaterService = theaterService;
    }

    @Override
    public Object call() {
        Timer t = new Timer();
        t.schedule(new DataValidatorTimedTask(theaterService), 5000L, INTERVAL);

        return null;
    }
}
