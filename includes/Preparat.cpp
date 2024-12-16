#include "Preparat.h"
#include <iostream>
#include <sstream>

using namespace std;

Preparat::Preparat(const string& nume, int calorii, const vector<string>& ingrediente, bool vegan, int pret, int gramaj, int timpPreparare)
    : Produs(nume, calorii, ingrediente, vegan, pret, gramaj), timpPreparare(timpPreparare) {}

void Preparat::afisare(int index) const {
    cout << "Ordin# " << index << " # : " << nume << ", " << calorii << " kcal, "
        << (vegan ? "vegan" : "non-vegan") << ", Pret: " << pret << " lei, "
        << "Gramaj: " << gramaj << " g, Timp preparare: " << timpPreparare << " min\n         Ingrediente: ";
    for (const auto& ing : ingrediente) cout << ing << " ";
    cout << endl;
}

unique_ptr<Produs> Preparat::clone() const {
    return make_unique<Preparat>(*this);
}

unique_ptr<Preparat> Preparat::dinFisier(const string& linie) {
    stringstream ss(linie);
    string nume, ingredienteStr, veganStr;
    int calorii, pret, gramaj, timpPreparare;
    vector<string> ingrediente;
    bool vegan;

    getline(ss, nume, ',');
    ss >> pret;
    ss.ignore();
    ss >> gramaj;
    ss.ignore();
    ss >> calorii;
    ss.ignore();
    getline(ss, ingredienteStr, ',');
    stringstream ssIngrediente(ingredienteStr);
    string ing;
    while (getline(ssIngrediente, ing, ';')) {
        ingrediente.push_back(ing);
    }
    ss >> timpPreparare;
    ss.ignore();
    getline(ss, veganStr);
    vegan = (veganStr == "da");

    return make_unique<Preparat>(nume, calorii, ingrediente, vegan, pret, gramaj, timpPreparare);
}
