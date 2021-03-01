package com.ubb.theatreapp.repository;

import com.ubb.theatreapp.entity.Spectacle;
import com.ubb.theatreapp.entity.Theater;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface SpectacleRepository extends JpaRepository<Spectacle, Long> {
    List<Spectacle> findAllByTheater(Theater t);
}
