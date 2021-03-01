package com.ubb.theatreapp.entity;

import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;

import javax.persistence.*;
import javax.validation.constraints.NotNull;
import java.time.LocalDate;
import java.util.List;
import java.util.Set;

@Entity
@Data
@Table(name="sales")
@NoArgsConstructor
@RequiredArgsConstructor
public class Sale {
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Id
    private long id;

    @ManyToOne(fetch = FetchType.EAGER, cascade = CascadeType.ALL, targetEntity = Spectacle.class)
    @JoinColumn(name = "spectacle_id", nullable = false)
    @NotNull
    @NonNull
    private Spectacle spectacle;

    @NonNull
    private LocalDate sellingDate;

    @ManyToOne(fetch = FetchType.EAGER, cascade = CascadeType.ALL, targetEntity = Theater.class)
    @NonNull
    private Theater theater;
}
