package com.ubb.theatreapp.exceptions;

public class PlaceAlreadyTakenException extends RuntimeException {
    public PlaceAlreadyTakenException() {
    }

    public PlaceAlreadyTakenException(String message) {
        super(message);
    }
}
