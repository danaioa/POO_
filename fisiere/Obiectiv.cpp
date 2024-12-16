#include "Obiectiv.h"
#include <cmath>

string Slabire::getObiectivString() const {
    return "Slabire";
}

int Slabire::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
    return static_cast<int>(std::round(10 * greutate + 6.25 * inaltime - 5 * varsta - 161));
}

string MasaMusculara::getObiectivString() const {
    return "Crestere masa musculara";
}

int MasaMusculara::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
    return static_cast<int>(10 * greutate + 6.25 * inaltime - 5 * varsta + 5);
}


string Mentinere::getObiectivString() const {
    return "Mentinere";
}

int Mentinere::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
    return static_cast<int>(10 * greutate + 6.25 * inaltime - 5 * varsta + 5);
}
