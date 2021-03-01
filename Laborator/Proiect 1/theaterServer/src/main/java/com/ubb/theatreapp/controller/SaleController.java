package com.ubb.theatreapp.controller;

import com.ubb.theatreapp.dto.SaleDto;
import com.ubb.theatreapp.entity.Sale;
import com.ubb.theatreapp.exceptions.PlaceAlreadyTakenException;
import com.ubb.theatreapp.runner.AddSaleTask;
import com.ubb.theatreapp.runner.Task;
import com.ubb.theatreapp.runner.TaskRunner;
import com.ubb.theatreapp.runner.TaskType;
import com.ubb.theatreapp.service.SaleService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;

@CrossOrigin(origins = "*", allowedHeaders = "*")
@RestController
@RequestMapping("sale")
public class SaleController {

    private TaskRunner taskRunner;
    private SaleService saleService;

    public SaleController(
            SaleService saleService,
            TaskRunner taskRunner) {
        this.saleService = saleService;
        this.taskRunner = taskRunner;
    }


    @GetMapping(value = "/test")
    public String test() {
        return "ok";
    }

    @PostMapping(value = "/add")
    public ResponseEntity<?> add(@RequestBody SaleDto s) throws Exception {
        try {
            Task t = taskRunner.builder(TaskType.ADD_SALE).args(s).build();
            Future<Object> futureId = taskRunner.addTask(t);
            return new ResponseEntity<>((Long) futureId.get(), HttpStatus.OK);
        } catch (ExecutionException e) {
            return new ResponseEntity<>(e.getMessage(), HttpStatus.NOT_ACCEPTABLE);
        }
    }
}
