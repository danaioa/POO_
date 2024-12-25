#include "Obiectiv.h"
#include <cmath>

string Slabire::getObiectivString() const {
    return "Slabire";
}

int Slabire::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
    int caloriiBaza = static_cast<int>(std::round(10 * greutate + 6.25 * inaltime - 5 * varsta));
    return gen == 1 ? caloriiBaza - 500 : caloriiBaza - 600;
}

string MasaMusculara::getObiectivString() const {
    return "Crestere masa musculara";
}

int MasaMusculara::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
    int caloriiBaza = static_cast<int>(std::round(10 * greutate + 6.25 * inaltime - 5 * varsta));
    return gen == 1 ? caloriiBaza + 500 : caloriiBaza + 400;
}

string Mentinere::getObiectivString() const {
    return "Mentinere";
}

int Mentinere::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
    int caloriiBaza = static_cast<int>(std::round(10 * greutate + 6.25 * inaltime - 5 * varsta));
    return gen == 1 ? caloriiBaza : caloriiBaza - 100;
}

string Definire::getObiectivString() const {
    return "Definire";
}

int Definire::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
    int caloriiBaza = static_cast<int>(std::round(10.0 * greutate + 6.25 * inaltime - 5.0 * varsta));
    return gen == 1 ? caloriiBaza - 500 : caloriiBaza - 300;
}