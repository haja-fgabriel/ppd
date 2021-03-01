package com.ubb.theatreapp.service;

import com.ubb.theatreapp.entity.PlaceSale;
import com.ubb.theatreapp.entity.Sale;
import com.ubb.theatreapp.entity.Spectacle;
import com.ubb.theatreapp.repository.PlaceSaleRepository;
import com.ubb.theatreapp.repository.SaleRepository;
import com.ubb.theatreapp.repository.SpectacleRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

@Service
public class SpectacleService {
    private final static Logger logger = Logger.getLogger(SpectacleService.class.getName());

    @Autowired
    private PlaceSaleRepository placeSaleRepository;

    @Autowired
    private SpectacleRepository spectacleRepository;

    @Autowired
    private SaleRepository saleRepository;

    public List<Integer> getTakenPlaces(long id) {
        List<Integer> result = new ArrayList<>();
        List<Sale> sales = saleRepository.getAllBySpectacleId(id);
        logger.info("Spectacle " + id + " has " + sales.size() + " sales");
        sales.forEach(s -> {
            List<PlaceSale> placeSales = placeSaleRepository.getAllBySaleId(s.getId());
            placeSales.forEach(ps -> result.add(ps.getPlace()));
        });

        return result;
    }
}
