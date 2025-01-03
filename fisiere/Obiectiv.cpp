#include "Obiectiv.h"
#include "ExceptieFitness.h"
#include <cmath>

void Obiectiv::valideazaDate(int greutate, int inaltime, int varsta, int gen) {
    if (greutate <= 0) {
        throw ExceptieGreutateInvalida();
    }
    if (inaltime < 50 || inaltime > 250) {
        throw ExceptieInaltimeInvalida();
    }
    if (varsta <= 0) {
        throw ExceptieVarstaInvalida();
    }
    if (gen != 1 && gen != 0) {
        throw ExceptieGenInvalid();
    }
}

string Slabire::getObiectivString() const {
    return "Slabire";
}

int Slabire::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
    valideazaDate(greutate, inaltime, varsta, gen);
    int caloriiBaza = static_cast<int>(std::round(10 * greutate + 6.25 * inaltime - 5 * varsta));
    int calorii = gen == 1 ? caloriiBaza - 500 : caloriiBaza - 600;
    return std::max(calorii, 0);
}

string MasaMusculara::getObiectivString() const {
    return "Crestere masa musculara";
}

int MasaMusculara::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
    valideazaDate(greutate, inaltime, varsta, gen);
    int caloriiBaza = static_cast<int>(std::round(10 * greutate + 6.25 * inaltime - 5 * varsta));
    int calorii = gen == 1 ? caloriiBaza + 500 : caloriiBaza + 400;
    return std::max(calorii, 0);
}

string Mentinere::getObiectivString() const {
    return "Mentinere";
}

int Mentinere::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
    valideazaDate(greutate, inaltime, varsta, gen);
    int caloriiBaza = static_cast<int>(std::round(10 * greutate + 6.25 * inaltime - 5 * varsta));
    int calorii = gen == 1 ? caloriiBaza : caloriiBaza - 100;
    return std::max(calorii, 0);
}

string Definire::getObiectivString() const {
    return "Definire";
}

int Definire::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
    valideazaDate(greutate, inaltime, varsta, gen);
    int caloriiBaza = static_cast<int>(std::round(10 * greutate + 6.25 * inaltime - 5 * varsta));
    int calorii = gen == 1 ? caloriiBaza - 500 : caloriiBaza - 300;
    return std::max(calorii, 0);
}
