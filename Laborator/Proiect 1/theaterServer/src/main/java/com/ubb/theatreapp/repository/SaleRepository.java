package com.ubb.theatreapp.repository;

import com.ubb.theatreapp.entity.Sale;
import com.ubb.theatreapp.entity.Theater;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface SaleRepository extends JpaRepository<Sale, Long> {
    List<Sale> getAllBySpectacleId(long id);

    @Query(value = "select ps.place from sales as s inner join placesales as ps on s.id=ps.sale_id "
            + "where s.title=:spect_id", nativeQuery = true)
    List<Integer> getTakenPlacesById(@Param("spect_id") long id);

    @Query(value = "select exists(select * from sales as s inner join placesales as ps on s.id=ps.sale_id "
            + "where s.spectacle_id=:spect_id and ps.place=:place)", nativeQuery = true)
    int existsPlaceForSpectacleId(@Param("place") int place, @Param("spect_id") long id);

    @Query(value = "select count(*) from sales as s inner join placesales as ps on s.id=ps.sale_id "
            + "where s.spectacle_id=:spect_id", nativeQuery = true)
    int countPlacesForSpectacleId(@Param("spect_id") long id);
}
