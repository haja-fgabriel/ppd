package com.ubb.theatreapp.entity;

import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;

import javax.persistence.*;
import java.time.LocalDateTime;

@Entity
@Data
@Table(name="validation_report")
@NoArgsConstructor
@RequiredArgsConstructor
public class ValidationReport {
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Id
    private long id;

    public static enum ErrorReason {
        INCORRECT_BALANCE
    }

    @NonNull
    private LocalDateTime dateTime;

    @NonNull
    boolean isValid;

    ErrorReason errorReason;
}
