#include "Antrenor.h"

Antrenor::Antrenor(std::string nume, std::string specializare, double tarif)
    : nume(std::move(nume)), specializare(std::move(specializare)), tarif(tarif) {}
