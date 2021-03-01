package com.ubb.theatreapp.repository;

import com.ubb.theatreapp.entity.ValidationReport;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface ValidationReportRepository extends JpaRepository<ValidationReport, Long> {
}
