#include "Desert.h"
#include <sstream>

Desert::Desert(const string& nume, int calorii, const vector<string>& ingrediente, bool vegan, int pret, int gramaj, int cantitate)
    : Produs(nume, calorii, ingrediente, vegan, pret, gramaj), cantitate(cantitate) {}

void Desert::afisare(int index) const {
    cout << "Ordin# " << index << " # : " << nume << ", " << calorii << " kcal, "
        << (vegan ? "vegan" : "non-vegan") << ", Pret: " << pret << " lei, "
        << "Gramaj: " << gramaj << " g, Cantitate: " << cantitate << " g\n        Ingrediente: ";
    for (const auto& ing : ingrediente) cout << ing << " ";
    cout << endl;
}

unique_ptr<Produs> Desert::clone() const {
    return make_unique<Desert>(*this);
}

unique_ptr<Desert> Desert::dinFisier(const string& linie) {
    std::stringstream ss(linie);
    string nume, ingredienteStr, veganStr;
    int calorii, pret, gramaj, cantitate;
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
    ss >> cantitate;
    ss.ignore();
    getline(ss, veganStr);
    vegan = (veganStr == "da");

    return make_unique<Desert>(nume, calorii, ingrediente, vegan, pret, gramaj, cantitate);
}
