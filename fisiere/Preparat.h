#ifndef PREPARAT_H
#define PREPARAT_H

#include "Produs.h"
#include <memory>
#include <vector>
#include <string>

class Preparat : public Produs {
    int timpPreparare;

public:
    Preparat(const std::string& nume, int calorii, const std::vector<std::string>& ingrediente, bool vegan, int pret, int gramaj, int timpPreparare);

    void afisare(int index) const override;

    [[nodiscard]] std::unique_ptr<Produs> clone() const override;

    static std::unique_ptr<Preparat> dinFisier(const std::string& linie);
};

#endif // PREPARAT_H
