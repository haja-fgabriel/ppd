package com.ubb.theatreapp.dto;

import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;

import java.time.LocalDate;
import java.util.List;

@Data
@NoArgsConstructor
@RequiredArgsConstructor
public class SaleDto {
    @NonNull
    private long spectacleId;

    @NonNull
    private LocalDate sellingDate;

    @NonNull
    private List<Integer> placeSales;
}
