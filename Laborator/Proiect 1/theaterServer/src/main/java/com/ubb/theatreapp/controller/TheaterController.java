package com.ubb.theatreapp.controller;

import com.ubb.theatreapp.service.TheaterService;
import org.springframework.web.bind.annotation.*;

@CrossOrigin(origins = "*", allowedHeaders = "*")
@RestController
@RequestMapping("theater")
public class TheaterController {
    private TheaterService theaterService;

    public TheaterController(TheaterService theaterService) {
        this.theaterService = theaterService;
    }

    @GetMapping("/{id}/count-places")
    public int getNumberOfPlaces(@PathVariable long id) {
        return theaterService.getNumberOfPlaces(id);
    }
}
