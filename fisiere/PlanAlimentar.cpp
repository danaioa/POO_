#include "PlanAlimentar.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <iomanip>
using namespace std;


PlanAlimentar::PlanAlimentar(int idClient, int caloriiDisponibile)
    : idClient(idClient), calorii(caloriiDisponibile) {}

string PlanAlimentar::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, (last - first + 1));
}

vector<MeniuItem> PlanAlimentar::citesteProduseDinFisier(const string& fisier, const string& categorie) {
    ifstream f(fisier);
    vector<MeniuItem> produse;
    string linie;

    if (!f.is_open()) {
        cerr << "eroare la deschiderea fisierului " << fisier << endl;
        return produse;
    }

    while (getline(f, linie)) {
        stringstream ss(linie);
        string nume;
        int calorii;
        float pret;
        getline(ss, nume, ',');
        ss >> pret;
        ss.ignore(1, ',');
        ss >> calorii;
        produse.emplace_back(trim(nume), calorii, pret, categorie);
    }

    return produse;
}


void PlanAlimentar::amestecaProduse(std::vector<MeniuItem>& produse) {
    static std::random_device rd;
    static std::mt19937 g(rd());

    for (size_t i = produse.size() - 1; i > 0; --i) {
        size_t j = g() % (i + 1);
        std::swap(produse[i], produse[j]);
    }
}

void PlanAlimentar::construiesteMeniu(int nrZile, bool alegereManuala) const {
    vector<MeniuItem> produseMicDejun = citesteProduseDinFisier("micdejun.txt", "MicDejun");
    vector<MeniuItem> produsePranz = citesteProduseDinFisier("pranz.txt", "Pranz");
    vector<MeniuItem> produseCina = citesteProduseDinFisier("cina.txt", "Cina");
    vector<MeniuItem> produseDesert = citesteProduseDinFisier("gustari.txt", "Desert");
    int caloriiZi = calorii;
    float totalPret = 0.0;

    for (int zi = 1; zi <= nrZile; ++zi) {
        cout << "\n--- ziua " << zi << " ---\n";
        cout << "calorii disponibile pentru ziua " << zi << ": " << caloriiZi << "\n";

        int caloriiDisponibile = caloriiZi;
        vector<MeniuItem> meniuZi;

        amestecaProduse(produseMicDejun);
        amestecaProduse(produsePranz);
        amestecaProduse(produseCina);
        amestecaProduse(produseDesert);

        while (caloriiDisponibile > 0) {
            bool produsAdaugat = false;

            for (const auto& produs : produseMicDejun) {
                if (produs.calorii <= caloriiDisponibile) {
                    meniuZi.push_back(produs);
                    caloriiDisponibile -= produs.calorii;
                    totalPret += produs.pret;
                    produsAdaugat = true;
                    break;
                }
            }

            for (const auto& produs : produsePranz) {
                if (produs.calorii <= caloriiDisponibile) {
                    meniuZi.push_back(produs);
                    caloriiDisponibile -= produs.calorii;
                    totalPret += produs.pret;
                    produsAdaugat = true;
                    break;
                }
            }

            for (const auto& produs : produseCina) {
                if (produs.calorii <= caloriiDisponibile) {
                    meniuZi.push_back(produs);
                    caloriiDisponibile -= produs.calorii;
                    totalPret += produs.pret;
                    produsAdaugat = true;
                    break;
                }
            }

            for (const auto& produs : produseDesert) {
                if (produs.calorii <= caloriiDisponibile) {
                    meniuZi.push_back(produs);
                    caloriiDisponibile -= produs.calorii;
                    totalPret += produs.pret;
                    produsAdaugat = true;
                    break;
                }
            }

            if (!produsAdaugat) {
                break;
            }
        }

        cout << "Meniul pentru ziua " << zi << ":\n";
        for (const auto& produs : meniuZi) {
            cout << produs.nume << " | calorii: " << produs.calorii << " | pret: " << produs.pret << " lei\n";
        }
    }

    cout << "\nTotal pret pentru " << nrZile << " zile: " << fixed << setprecision(2) << totalPret << " lei\n";
}



string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, (last - first + 1));
}

int getCaloriiById(int id) {
    ifstream fisier("Clienti.txt");
    if (!fisier.is_open()) {
        cerr << "Eroare la deschiderea fisierului Clienti.txt!" << endl;
        return -1;
    }

    string linie;
    while (getline(fisier, linie)) {
        if (linie.find("ID: ") == 0) {
            int idFisier = stoi(linie.substr(4));

            if (idFisier == id) {
                while (getline(fisier, linie)) {
                    if (linie.find("Calorii: ") == 0) {
                        string caloriiStr = linie.substr(9);
                        caloriiStr = trim(caloriiStr);

                        try {
                            return stoi(caloriiStr);
                        }
                        catch (const invalid_argument& ) {
                            cerr << "Eroare la citirea caloriilor pentru clientul cu ID-ul " << id << endl;
                            return -1;
                        }
                    }
                }
            }
        }
    }

    return -1;
}
