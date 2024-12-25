#ifndef MENIU_PRINCIPAL_H
#define MENIU_PRINCIPAL_H

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include "Produs.h"

class MeniuPrincipal {
    std::vector<std::unique_ptr<Produs>> produse;

public:
    void adaugaProdus(std::unique_ptr<Produs> produs);

    [[nodiscard]] const std::vector<std::unique_ptr<Produs>>& getProduse() const;

    void afiseazaMeniu() const;

    //std::unique_ptr<Produs> selecteazaProdus(int index);

    [[nodiscard]] size_t getNrProduse() const;

    void citesteProduseDinFisier(const std::string& numeFisier, bool esteBautura = false);

    template <typename T>
    void citesteProduseDinFisier(const std::string& numeFisier, MeniuPrincipal& meniu) {
        std::ifstream fisier(numeFisier);
        if (!fisier.is_open()) {
            throw std::runtime_error("Eroare la deschiderea fisierului: " + numeFisier);
        }

        std::string linie;
        while (std::getline(fisier, linie)) {
            if (linie.empty()) continue;

            try {
                meniu.adaugaProdus(T::dinFisier(linie));
            } catch (const std::exception& e) {
                std::cout << "Eroare la citirea produsului din linia: " << linie << ". Detalii: " << e.what() << std::endl;
            }
        }

        fisier.close();
    }
};

#endif // MENIU_PRINCIPAL_H
