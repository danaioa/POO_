#ifndef EXCEPTIEFITNESS_H
#define EXCEPTIEFITNESS_H

#include <stdexcept>
#include <string>

class ExceptieFitness : public std::exception {
protected:
    std::string mesaj;

public:
    explicit ExceptieFitness(const std::string& msg) : mesaj(msg) {}
    virtual const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

class ExceptieGreutateInvalida : public ExceptieFitness {
public:
    explicit ExceptieGreutateInvalida(const std::string& msg = "Greutate invalida! Greutatea trebuie sa fie mai mare decat 0.")
        : ExceptieFitness(msg) {}
};

class ExceptieInaltimeInvalida : public ExceptieFitness {
public:
    explicit ExceptieInaltimeInvalida(const std::string& msg = "Inaltime invalida! Inaltimea trebuie sa fie intre 50 si 250 cm.")
        : ExceptieFitness(msg) {}
};

class ExceptieVarstaInvalida : public ExceptieFitness {
public:
    explicit ExceptieVarstaInvalida(const std::string& msg = "Varsta invalida! Varsta trebuie sa fie un numar pozitiv.")
        : ExceptieFitness(msg) {}
};

class ExceptieGenInvalid : public ExceptieFitness {
public:
    explicit ExceptieGenInvalid(const std::string& msg = "Gen invalid! Genul trebuie sa fie 1 (masculin) sau 0 (feminin).")
        : ExceptieFitness(msg) {}
};

#endif // EXCEPTIEFITNESS_H
