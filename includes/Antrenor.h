#ifndef ANTRENOR_H
#define ANTRENOR_H

#include <string>

struct Antrenor {
    std::string nume;
    std::string specializare;
    double tarif;

    Antrenor(std::string nume, std::string specializare, double tarif);
};

#endif // ANTRENOR_H
