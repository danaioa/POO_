#ifndef DESERT_H
#define DESERT_H

#include "Produs.h"
class Desert : public Produs {
    int cantitate;

public:
    Desert(const string& nume, int calorii, const vector<string>& ingrediente, bool vegan, int pret, int gramaj, int cantitate);

    void afisare(int index) const override;

    [[nodiscard]] unique_ptr<Produs> clone() const override;

    static unique_ptr<Desert> dinFisier(const string& linie);
};

#endif // DESERT_H
