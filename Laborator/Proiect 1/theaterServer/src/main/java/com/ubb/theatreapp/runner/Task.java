package com.ubb.theatreapp.runner;

import com.ubb.theatreapp.service.SaleService;

import java.util.concurrent.Callable;

public interface Task extends Callable<Object> {

}
