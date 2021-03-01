package com.ubb.theatreapp.runner;

import com.ubb.theatreapp.service.TheaterService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Configurable;
import org.springframework.stereotype.Component;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.TimerTask;
import java.util.logging.Logger;

public class DataValidatorTimedTask extends TimerTask {
    private final static Logger logger = Logger.getLogger(DataValidatorTimedTask.class.getName());

    private TheaterService theaterService;

    public DataValidatorTimedTask(TheaterService theaterService) {
        this.theaterService = theaterService;
    }

    @Override
    public void run() {
        // TODO make validations
        logger.info("merge :))");
        if (theaterService == null)
            System.out.println("NU E OK");
        theaterService.checkDataValidity();
    }
}
