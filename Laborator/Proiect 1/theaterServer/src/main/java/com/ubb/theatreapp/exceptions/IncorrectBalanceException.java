package com.ubb.theatreapp.exceptions;

public class IncorrectBalanceException extends RuntimeException {
    public IncorrectBalanceException() {
        super();
    }

    public IncorrectBalanceException(String message) {
        super(message);
    }
}
