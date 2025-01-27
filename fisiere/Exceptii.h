#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <exception>
#include <string>
#include <utility>

class ExceptieGenerala : public std::exception {
protected:
    std::string mesaj;
public:
    explicit ExceptieGenerala(std::string  mesaj) : mesaj(std::move(mesaj)) {}
    [[nodiscard]] const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

class ExceptieFisier : public ExceptieGenerala {
public:
    explicit ExceptieFisier(const std::string& fisier)
        : ExceptieGenerala("Eroare: Nu s-a putut deschide fisierul \"" + fisier + "\".") {}
};

class ExceptieOptiuneInvalida : public ExceptieGenerala {
public:
    ExceptieOptiuneInvalida()
        : ExceptieGenerala("Eroare: Optiune invalida selectata! Te rog, selecteaza o optiune valida.") {}


    explicit ExceptieOptiuneInvalida(const std::string& mesaj)
        : ExceptieGenerala("Eroare: " + mesaj) {}
};


class ExceptieGreutateInvalida : public ExceptieGenerala {
public:
    ExceptieGreutateInvalida()
        : ExceptieGenerala("Eroare: Greutatea introdusa este invalida (trebuie sa fie un numar pozitiv).") {}
};

class ExceptieInaltimeInvalida : public ExceptieGenerala {
public:
    ExceptieInaltimeInvalida()
        : ExceptieGenerala("Eroare: Inaltimea introdusa este invalida (trebuie sa fie intre 50 si 250 cm).") {}
};

class ExceptieVarstaInvalida : public ExceptieGenerala {
public:
    ExceptieVarstaInvalida()
        : ExceptieGenerala("Eroare: Varsta introdusa este invalida (trebuie sa fie un numar pozitiv).") {}
};

class ExceptieGenInvalid : public ExceptieGenerala {
public:
    ExceptieGenInvalid()
        : ExceptieGenerala("Eroare: Genul introdus este invalid (trebuie sa fie 0 sau 1).") {}
};

#endif // EXCEPTII_H
