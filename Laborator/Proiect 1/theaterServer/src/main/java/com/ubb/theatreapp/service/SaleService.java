package com.ubb.theatreapp.service;

import com.ubb.theatreapp.dto.SaleDto;
import com.ubb.theatreapp.entity.PlaceSale;
import com.ubb.theatreapp.entity.Sale;
import com.ubb.theatreapp.entity.Spectacle;
import com.ubb.theatreapp.exceptions.PlaceAlreadyTakenException;
import com.ubb.theatreapp.repository.PlaceSaleRepository;
import com.ubb.theatreapp.repository.SaleRepository;
import com.ubb.theatreapp.repository.SpectacleRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.logging.Logger;

@Service
@Transactional
public class SaleService {
    private final static Logger logger = Logger.getLogger(SaleService.class.getName());

    @Autowired
    private SaleRepository saleRepository;

    @Autowired
    private PlaceSaleRepository placeSaleRepository;

    @Autowired
    private SpectacleRepository spectacleRepository;

    public long add(SaleDto s) {
        logger.info("Creating Sale instance");
        Sale sa = new Sale();
        sa.setSellingDate(s.getSellingDate());
        Spectacle spectacle = spectacleRepository.getOne(s.getSpectacleId());
        sa.setSpectacle(spectacle);
        sa.setTheater(sa.getSpectacle().getTheater());

        logger.info("Checking for already taken places");
        s.getPlaceSales().forEach(place -> {
            if (saleRepository.existsPlaceForSpectacleId(place, s.getSpectacleId()) > 0) {
                throw new PlaceAlreadyTakenException();
            }
        });

        logger.info("Saving Sale instance to the database");

        saleRepository.save(sa);

        logger.info("Sale instance has ID " + sa.getId());

        logger.info("Creating PlaceSale instances and saving them to the database");
        s.getPlaceSales().forEach(place -> {
            PlaceSale ps = new PlaceSale(place);
            ps.setSale(saleRepository.getOne(sa.getId()));
            placeSaleRepository.save(ps);
        });

        final long balance = spectacle.getBalance();
        int placesCount = s.getPlaceSales().size();
        spectacle.setBalance(balance + placesCount * spectacle.getTicketPrice());

        spectacleRepository.save(spectacle);

        return sa.getId();
    }
}
