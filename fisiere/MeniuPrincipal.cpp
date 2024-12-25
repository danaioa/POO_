#include "MeniuPrincipal.h"
#include "Bautura.h"
#include "Preparat.h"




void MeniuPrincipal::adaugaProdus(std::unique_ptr<Produs> produs) {
    produse.push_back(std::move(produs));
}

const std::vector<std::unique_ptr<Produs>>& MeniuPrincipal::getProduse() const {
    return produse;
}

void MeniuPrincipal::afiseazaMeniu() const {
    int index = 1;
    for (const auto& produs : produse) {
        produs->afisare(index);
        ++index;
    }
}

/*
std::unique_ptr<Produs> MeniuPrincipal::selecteazaProdus(int index) {
    if (index > 0 && static_cast<size_t>(index) <= produse.size()) {
        return std::move(produse[index - 1]);
    } else {
        std::cout << "Index invalid!" << std::endl;
        return nullptr;
    }
}
*/



size_t MeniuPrincipal::getNrProduse() const {
    return produse.size();
}

void MeniuPrincipal::citesteProduseDinFisier(const std::string& numeFisier, bool esteBautura) {
    std::ifstream fisier(numeFisier);
    if (!fisier.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului: " << numeFisier << std::endl;
        return;
    }

    std::string linie;
    while (std::getline(fisier, linie)) {
        if (linie.empty()) continue;

        if (esteBautura) {
            adaugaProdus(Bautura::dinFisier(linie));
        } else {
            adaugaProdus(Preparat::dinFisier(linie));
        }
    }
    fisier.close();
}
