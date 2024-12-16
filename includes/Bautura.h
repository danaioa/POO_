#ifndef BAUTURA_H
#define BAUTURA_H

#include "Produs.h"


class Bautura : public Produs {
public:
    Bautura(const string& nume, int calorii, const vector<string>& ingrediente, bool vegan, int pret, int gramaj);

    void afisare(int index) const override;

    [[nodiscard]] unique_ptr<Produs> clone() const override;

    static unique_ptr<Bautura> dinFisier(const string& linie);
};

#endif // BAUTURA_H

