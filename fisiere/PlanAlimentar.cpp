#include "PlanAlimentar.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <algorithm>

PlanAlimentar::PlanAlimentar(int idClient, int caloriiDisponibile)
    : idClient(idClient), calorii(caloriiDisponibile) {}

std::string PlanAlimentar::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, (last - first + 1));
}

std::vector<MeniuItem> PlanAlimentar::citesteProduseDinFisier(const std::string& fisier, const std::string& categorie) {
    std::ifstream f(fisier);
    std::vector<MeniuItem> produse;
    std::string linie;

    if (!f.is_open()) {
        std::cout << "eroare la deschiderea fisierului " << fisier << std::endl;
        return produse;
    }

    while (getline(f, linie)) {
        std::stringstream ss(linie);
        std::string nume;
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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::vector<MeniuItem>::size_type> distrib(0, produse.size() - 1);

    for (std::vector<MeniuItem>::size_type i = produse.size() - 1; i > 0; --i) {
        std::vector<MeniuItem>::size_type j = distrib(gen);
        std::swap(produse[i], produse[j]);
    }
}

void PlanAlimentar::construiesteMeniu(int nrZile, bool alegereManuala) const {
    std::vector<MeniuItem> produseMicDejun = citesteProduseDinFisier("micdejun.txt", "MicDejun");
    std::vector<MeniuItem> produsePranz = citesteProduseDinFisier("pranz.txt", "Pranz");
    std::vector<MeniuItem> produseCina = citesteProduseDinFisier("cina.txt", "Cina");
    std::vector<MeniuItem> produseDesert = citesteProduseDinFisier("gustari.txt", "Desert");

    int caloriiZi = calorii;
    float totalPret = 0.0;

    for (int zi = 1; zi <= nrZile; ++zi) {
        std::cout << "\n--- ziua " << zi << " ---\n";
        std::cout << "calorii disponibile pentru ziua " << zi << ": " << caloriiZi << "\n";

        int caloriiDisponibile = caloriiZi;
        std::vector<MeniuItem> meniuZi;

        if (alegereManuala) {
            std::cout << "Alege produsele pentru ziua " << zi << ":\n";


            std::cout << "\nAlege un mic dejun:\n";
            for (int i = 0; i < produseMicDejun.size(); ++i) {
                std::cout << i + 1 << ". " << produseMicDejun[i].nume << " | calorii: " << produseMicDejun[i].calorii << " | pret: " << produseMicDejun[i].pret << " lei\n";
            }
            int alegere;
            std::cin >> alegere;
            alegere--;
            if (produseMicDejun[alegere].calorii <= caloriiDisponibile) {
                meniuZi.push_back(produseMicDejun[alegere]);
                caloriiDisponibile -= produseMicDejun[alegere].calorii;
                totalPret += produseMicDejun[alegere].pret;
            } else {
                std::cout << "Alegerea depaseste numarul de calorii disponibile.\n";
                continue;
            }



        } else {
            std::vector<MeniuItem> produseDeZi;
            produseDeZi.insert(produseDeZi.end(), produseMicDejun.begin(), produseMicDejun.end());
            produseDeZi.insert(produseDeZi.end(), produsePranz.begin(), produsePranz.end());
            produseDeZi.insert(produseDeZi.end(), produseCina.begin(), produseCina.end());
            produseDeZi.insert(produseDeZi.end(), produseDesert.begin(), produseDesert.end());

            amestecaProduse(produseDeZi);

            while (caloriiDisponibile > 0 && !produseDeZi.empty()) {
                for (auto it = produseDeZi.begin(); it != produseDeZi.end(); ++it) {
                    if (it->calorii <= caloriiDisponibile) {
                        meniuZi.push_back(*it);
                        caloriiDisponibile -= it->calorii;
                        totalPret += it->pret;

                        it = produseDeZi.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
        }

        std::cout << "Meniul pentru ziua " << zi << ":\n";
        for (auto& produs : meniuZi) {
            std::cout << produs.nume << " | calorii: " << produs.calorii << " | pret: " << produs.pret << " lei\n";
        }

        if (caloriiDisponibile > 0) {
            std::cout << "Mai raman " << caloriiDisponibile << " calorii.\n";
        }
    }

    std::cout << "\nTotal pret pentru " << nrZile << " zile: " << std::fixed << std::setprecision(2) << totalPret << " lei\n";
}
