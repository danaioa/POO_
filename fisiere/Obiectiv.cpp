#include "Obiectiv.h"
#include  "ExceptieFitness.h"
#include <cmath>

string Slabire::getObiectivString() const {
    return "Slabire";
}

int Slabire::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
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

    int caloriiBaza = static_cast<int>(std::round(10 * greutate + 6.25 * inaltime - 5 * varsta));
    int calorii=gen == 1 ? caloriiBaza - 500 : caloriiBaza - 600;

    if (calorii < 0) {
        calorii = 0;
    }

    return calorii;
}


string MasaMusculara::getObiectivString() const {
    return "Crestere masa musculara";
}

int MasaMusculara::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
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

    int caloriiBaza = static_cast<int>(std::round(10 * greutate + 6.25 * inaltime - 5 * varsta));
    int calorii=gen == 1 ? caloriiBaza + 500 : caloriiBaza + 400;

    if (calorii < 0) {
        calorii = 0;
    }

    return calorii;
}

string Mentinere::getObiectivString() const {
    return "Mentinere";
}

int Mentinere::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
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

    int caloriiBaza = static_cast<int>(std::round(10 * greutate + 6.25 * inaltime - 5 * varsta));
    int calorii = gen == 1 ? caloriiBaza : caloriiBaza - 100;

    if (calorii < 0) {
        calorii = 0;
    }

    return calorii;
}


string Definire::getObiectivString() const {
    return "Definire";
}

int Definire::calculeazaCalorii(int greutate, int inaltime, int varsta, int gen) const {
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

    int caloriiBaza = static_cast<int>(std::round(10 * greutate + 6.25 * inaltime - 5 * varsta));
   int calorii= gen == 1 ? caloriiBaza - 500 : caloriiBaza - 300;


    if (calorii < 0) {
        calorii = 0;
    }

    return calorii;
}