package com.ubb.theatreapp.service;

import com.ubb.theatreapp.entity.Theater;
import com.ubb.theatreapp.entity.ValidationReport;
import com.ubb.theatreapp.exceptions.IncorrectBalanceException;
import com.ubb.theatreapp.repository.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.bind.annotation.PathVariable;

import java.time.LocalDateTime;
import java.util.concurrent.atomic.AtomicReference;
import java.util.logging.Logger;

@Service
public class TheaterService {
    private final static Logger logger = Logger.getLogger(TheaterService.class.getName());

    @Autowired
    private TheaterRepository theaterRepository;

    @Autowired
    private SaleRepository saleRepository;

    @Autowired
    private PlaceSaleRepository placeSaleRepository;

    @Autowired
    private SpectacleRepository spectacleRepository;

    @Autowired
    private ValidationReportRepository validationReportRepository;

    public int getNumberOfPlaces(@PathVariable long id) {
        Theater t = theaterRepository.getOne(id);
        return t.getNumberPlaces();
    }

    public void checkDataValidity() {
        logger.info("Checking validity of currently saved data");
        try {
            seekRepositories();
            validationReportRepository.save(new ValidationReport(LocalDateTime.now(), true));
        } catch (IncorrectBalanceException e) {
            ValidationReport report = new ValidationReport(LocalDateTime.now(), false);
            report.setErrorReason(ValidationReport.ErrorReason.INCORRECT_BALANCE);
            validationReportRepository.save(report);
        }
    }

    private void seekRepositories() {
        logger.info("Seeking repositories");

        theaterRepository.findAll().forEach(theater -> {
            logger.info("Seeking spectacles for theater " + theater.getId());

            int numberPlaces = theater.getNumberPlaces();

            spectacleRepository.findAllByTheater(theater).forEach(spectacle -> {
                logger.info("Verifying balance for spectacle " + spectacle.getId());

                long ticketPrice = spectacle.getTicketPrice();
                long balance = spectacle.getBalance();
                int count = saleRepository.countPlacesForSpectacleId(spectacle.getId());
                if ((long) count * ticketPrice != balance)
                    throw new IncorrectBalanceException();
            });
        });
    }
}
