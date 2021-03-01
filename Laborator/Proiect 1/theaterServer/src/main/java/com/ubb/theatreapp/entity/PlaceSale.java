package com.ubb.theatreapp.entity;

import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;

import javax.persistence.*;

@Entity
@Data
@Table(name = "placesales")
@NoArgsConstructor
@RequiredArgsConstructor
public class PlaceSale {
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Id
    private long id;

    @ManyToOne(fetch = FetchType.EAGER, cascade = CascadeType.ALL, targetEntity = Sale.class)
    @JoinColumn(name = "sale_id", nullable = false)
    private Sale sale;

    @NonNull
    private int place;
}
