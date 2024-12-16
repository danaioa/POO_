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

#endif // EXCEPTII_H
