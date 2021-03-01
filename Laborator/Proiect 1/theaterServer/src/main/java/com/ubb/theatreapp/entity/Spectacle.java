package com.ubb.theatreapp.entity;

import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;
import org.hibernate.annotations.Fetch;
import org.springframework.web.bind.annotation.RequestBody;

import javax.persistence.*;
import javax.validation.constraints.NotNull;
import java.time.LocalDate;
import java.util.List;

@Entity
@Table(name = "spectacles")
@Data
@NoArgsConstructor
@RequiredArgsConstructor
public class Spectacle {
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Id
    private long id;

    @NonNull
    private LocalDate data;

    @NonNull
    private String title;

    @NonNull
    private long ticketPrice;

    private long balance;

    @ManyToOne(fetch = FetchType.EAGER, cascade = CascadeType.ALL, targetEntity = Theater.class)
    @JoinColumn(name = "theater_id")
    private Theater theater;

    @OneToMany(mappedBy = "theater", fetch = FetchType.EAGER, cascade = CascadeType.ALL)
    private List<Sale> sales;
}
