package com.ubb.theatreapp.runner;

import com.ubb.theatreapp.dto.SaleDto;
import com.ubb.theatreapp.service.SaleService;

public class AddSaleTask implements Task {
    private SaleDto saleDto;
    private SaleService saleService;

    public AddSaleTask(SaleService s, SaleDto sale) {
        this.saleService = s;
        saleDto = sale;
    }

    @Override
    public Long call() throws Exception {
        return saleService.add(saleDto);
    }
}
