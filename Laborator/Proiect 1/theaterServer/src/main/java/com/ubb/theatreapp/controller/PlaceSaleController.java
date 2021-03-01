package com.ubb.theatreapp.controller;

import com.ubb.theatreapp.service.PlaceSaleService;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@CrossOrigin(origins = "*", allowedHeaders = "*")
@RestController
@RequestMapping(name = "placesale")
public class PlaceSaleController {
    private PlaceSaleService placeSaleService;

    public PlaceSaleController(PlaceSaleService placeSaleService) {
        this.placeSaleService = placeSaleService;
    }

    @GetMapping(value = "/test")
    public String test() {
        return "ok";
    }
}
