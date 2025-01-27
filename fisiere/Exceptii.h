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
        : ExceptieGenerala("Eroare: Nu s-a putut deschide fișierul \"" + fisier + "\".") {}
};

class ExceptieOptiuneInvalida : public ExceptieGenerala {
public:
    ExceptieOptiuneInvalida()
        : ExceptieGenerala("Eroare: Opțiune invalidă selectată! Te rog, selectează o opțiune validă.") {}


    explicit ExceptieOptiuneInvalida(const std::string& mesaj)
        : ExceptieGenerala("Eroare: " + mesaj) {}
};


class ExceptieGreutateInvalida : public ExceptieGenerala {
public:
    ExceptieGreutateInvalida()
        : ExceptieGenerala("Eroare: Greutatea introdusă este invalidă (trebuie să fie un număr pozitiv).") {}
};

class ExceptieInaltimeInvalida : public ExceptieGenerala {
public:
    ExceptieInaltimeInvalida()
        : ExceptieGenerala("Eroare: Înălțimea introdusă este invalidă (trebuie să fie între 50 și 250 cm).") {}
};

class ExceptieVarstaInvalida : public ExceptieGenerala {
public:
    ExceptieVarstaInvalida()
        : ExceptieGenerala("Eroare: Vârsta introdusă este invalidă (trebuie să fie un număr pozitiv).") {}
};

class ExceptieGenInvalid : public ExceptieGenerala {
public:
    ExceptieGenInvalid()
        : ExceptieGenerala("Eroare: Genul introdus este invalid (trebuie să fie 0 sau 1).") {}
};

#endif // EXCEPTII_H
