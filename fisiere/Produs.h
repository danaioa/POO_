#ifndef PRODUS_H
#define PRODUS_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::cout;
using std::endl;

class Produs {
protected:
    string nume;
    int calorii;
    vector<string> ingrediente;
    bool vegan;
    int pret;
    int gramaj;

public:
    Produs(string nume, int calorii, const vector<string>& ingrediente, bool vegan, int pret, int gramaj);

    virtual void afisare(int index) const;

    [[nodiscard]] virtual unique_ptr<Produs> clone() const = 0;
    virtual ~Produs() = default;

    [[nodiscard]] int getPret() const;
    [[nodiscard]] string getNume() const;
};

#endif
