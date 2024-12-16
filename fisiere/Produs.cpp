#include "Produs.h"
#include "ProdusException.h"

Produs::Produs(string nume, int calorii, const vector<string>& ingrediente, bool vegan, int pret, int gramaj)
    : nume(std::move(nume)), calorii(calorii), ingrediente(ingrediente), vegan(vegan), pret(pret), gramaj(gramaj) {
    if (pret <= 0 || gramaj <= 0) {
        throw ProdusInvalidException("Pretul si gramajul produsului trebuie sa fie pozitive.");
    }
}

void Produs::afisare(int index) const {
    cout << "Ordin#" << index << "# " << nume << ", " << calorii << " kcal, "
        << (vegan ? "vegan" : "non-vegan") << ", Pret: " << pret << " lei, "
        << "Gramaj: " << gramaj << " g\n        Ingrediente: ";
    for (const auto& ing : ingrediente) cout << ing << " ";
    cout << endl;
}

int Produs::getPret() const {
    return pret;
}

string Produs::getNume() const {
    return nume;
}
