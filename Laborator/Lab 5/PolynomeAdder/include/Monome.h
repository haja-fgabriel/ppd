#pragma once

struct Monome {
    int Degree;
    double Coefficient;

    bool operator==(const Monome& m) const
    {
        return m.Degree == Degree;
    }
};