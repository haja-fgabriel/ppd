package com.ubb.theatreapp.entity;

import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;

import javax.persistence.*;
import java.util.List;
import java.util.Set;

@Entity
@Data
@Table(name="theaters")
@NoArgsConstructor
//@RequiredArgsConstructor
public class Theater {
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Id
    private long id;

    @NonNull
    private int numberPlaces;

    @OneToMany(mappedBy = "theater")
    Set<Spectacle> spectacles;

    @OneToMany(mappedBy = "theater")
    Set<Sale> sales;
}

