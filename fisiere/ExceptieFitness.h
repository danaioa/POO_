#ifndef EXCEPTIEFITNESS_H
#define EXCEPTIEFITNESS_H

#include <stdexcept>
#include <string>

class ExceptieGreutateInvalida : public std::runtime_error {
public:
    ExceptieGreutateInvalida() : std::runtime_error("Greutatea trebuie sa fie mai mare decat 0.") {}
};

class ExceptieInaltimeInvalida : public std::runtime_error {
public:
    ExceptieInaltimeInvalida() : std::runtime_error("Inaltimea trebuie sa fie intre 50 si 250 cm.") {}
};

class ExceptieVarstaInvalida : public std::runtime_error {
public:
    ExceptieVarstaInvalida() : std::runtime_error("Varsta trebuie sa fie mai mare decat 0.") {}
};

class ExceptieGenInvalid : public std::runtime_error {
public:
    ExceptieGenInvalid() : std::runtime_error("Genul trebuie sa fie 0 (feminin) sau 1 (masculin).") {}
};

#endif // EXCEPTIEFITNESS_H
