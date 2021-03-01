package com.ubb.theatreapp.controller;

import com.ubb.theatreapp.repository.SpectacleRepository;
import com.ubb.theatreapp.service.SpectacleService;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@CrossOrigin(origins = "*")
@RestController
@RequestMapping("spectacle")
public class SpectacleController {
    private SpectacleService spectacleService;

    public SpectacleController(SpectacleService spectacleService) {
        this.spectacleService = spectacleService;
    }

    @GetMapping(value="/test")
    public String test() {
        return "ok";
    }

    @GetMapping(value="/{id}/taken-places")
    public List<Integer> getTakenPlaces(@PathVariable long id) {
        return spectacleService.getTakenPlaces(id);
    }
}
