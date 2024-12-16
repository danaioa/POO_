#include "Bautura.h"
#include <sstream>

Bautura::Bautura(const string& nume, int calorii, const vector<string>& ingrediente, bool vegan, int pret, int gramaj)
    : Produs(nume, calorii, ingrediente, vegan, pret, gramaj) {}

void Bautura::afisare(int index) const {
    cout << "Ordin#" << index << "#  " << nume << ", " << calorii << " kcal, "
        << (vegan ? "vegan" : "non-vegan") << ", Pret: " << pret << " lei, "
        << "Gramaj: " << gramaj << " g\n        Ingrediente: ";
    for (const auto& ing : ingrediente) cout << ing << " ";
    cout << endl;
}

unique_ptr<Produs> Bautura::clone() const {
    return make_unique<Bautura>(*this);
}

unique_ptr<Bautura> Bautura::dinFisier(const string& linie) {
   std:: stringstream ss(linie);
    string nume, ingredienteStr, veganStr;
    int calorii, pret, gramaj;
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
    std::stringstream ssIngrediente(ingredienteStr);
    string ing;
    while (getline(ssIngrediente, ing, ';')) {
        ingrediente.push_back(ing);
    }
    getline(ss, veganStr);
    vegan = (veganStr == "da");

    return make_unique<Bautura>(nume, calorii, ingrediente, vegan, pret, gramaj);
}
