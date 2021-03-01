package com.ubb.theatreapp.service;

import com.ubb.theatreapp.repository.PlaceSaleRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class PlaceSaleService {
    @Autowired
    private PlaceSaleRepository placeSaleRepository;
}
