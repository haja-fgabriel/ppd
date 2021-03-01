package com.ubb.theatreapp.repository;

import com.ubb.theatreapp.entity.PlaceSale;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface PlaceSaleRepository extends JpaRepository<PlaceSale, Long> {
    List<PlaceSale> getAllBySaleId(long id);
}
