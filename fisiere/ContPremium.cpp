#include <random>
#include <fstream>
#include <iostream>
#include "ContPremium.h"
#include "Exceptii.h"
#include "PlanAlimentar.h"

ContPremium::ContPremium(std::unique_ptr<Client> clientPtr)
    : Cont(clientPtr->getId_Client(), clientPtr->getNume(), clientPtr->getTelefon(), clientPtr->getAdresa()),
      obiectiv(nullptr),
      clientPremium(std::move(clientPtr)){ }


ContPremium::ContPremium(int id, const std::string& nume, const std::string& telefon, const std::string& adresa)
    : Cont(id, nume, telefon, adresa),
      obiectiv(nullptr),
      clientPremium(std::make_unique<Client>(id, nume, telefon, adresa)){ }





ContPremium::~ContPremium() {
    delete obiectiv;
}

double ContPremium::getCostCont() {
    return costCont;
}

double ContPremium::costlivrare() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(1, 20);
    double costLivrare = dist(rng);
    costLivrare *= 0.85;  // reducere de 15% pentru cont premium
    return costLivrare;
}



void ContPremium::setObiectiv(Obiectiv* obj) {
    delete obiectiv;
    obiectiv = obj;
}

Obiectiv* ContPremium::alegeObiectiv() {
    int optiune;
    std::cout << "Alege obiectivul:\n";
    std::cout << "1. Slabire\n";
    std::cout << "2. Crestere masa musculara\n";
    std::cout << "3. Mentinere\n";
    std::cout << "Alegere: ";
    std::cin >> optiune;

    Obiectiv* obj = nullptr;
    switch (optiune) {
        case 1:
            obj = new Slabire();
            break;
        case 2:
            obj = new MasaMusculara();
            break;
        case 3:
            obj = new Mentinere();
            break;
        default:
            throw ExceptieOptiuneInvalida();
    }

    return obj;
}

std::unique_ptr<Cont> ContPremium::clone() const {
    auto cont = std::make_unique<ContPremium>(std::make_unique<Client>(*client));
    if (obiectiv) {
        cont->setObiectiv(obiectiv);
    }
    return cont;
}

void ContPremium::rezervaMasa() {
    try {
        std::ifstream fisier("mese.txt");
        if (!fisier.is_open()) {
            throw ExceptieFisier("Nu s-a putut deschide fișierul mese.txt.");
        }

        std::vector< std::pair<int, bool>> mese(5, { 0, false });
        std::string linie;
        int masaIndex = 0;
        std::vector<std::string> ore = { "18:00 - 20:00", "20:00 - 22:00", "22:00 - 00:00" };

        while (getline(fisier, linie)) {
            if (linie.find("rezervata") != std::string::npos) {
                mese[masaIndex].second = true; // masa rezervata
            }
            masaIndex++;
        }

        int alegere;
        bool intervalDisponibil = false;
        while (!intervalDisponibil) {
            std::cout << "Alege un interval orar pentru rezervare:\n";
            for (size_t i = 0; i < ore.size(); ++i) {
                std::cout << i + 1 << ". " << ore[i] << std::endl;
            }

            std::cin >> alegere;

            if (alegere < 1 || alegere > 3) {
                std::cout << "Optiune invalida. Te rog alege un interval valid.\n";
                continue;
            }

            int masaAleasa = -1;
            for (size_t i = 0; i < mese.size(); ++i) {
                if (!mese[i].second) {
                    masaAleasa = static_cast<int>(i);
                    break;
                }
            }

            if (masaAleasa == -1) {
                std::cout << "Nu mai sunt mese disponibile pentru acest interval.\n";
                std::cout << "Te rugam sa alegi un alt interval.\n";
            } else {
                intervalDisponibil = true;
                std::cout << "Ai ales masa " << masaAleasa + 1 << " pentru intervalul " << ore[alegere - 1] << ".\n";
                mese[masaAleasa].second = true;

                std::ofstream outFisier("mese.txt");
                if (!outFisier.is_open()) {
                    throw ExceptieFisier("Nu s-a putut deschide fișierul mese.txt pentru scriere.");
                }

                for (size_t i = 0; i < mese.size(); ++i) {
                    outFisier << "Masa " << i + 1 << " " << ore[i] << " este " << (mese[i].second ? "rezervata" : "disponibila") << "\n";
                }

                std::cout << "\n--- Confirmare rezervare ---\n";
                std::cout << "Ati rezervat Masa " << masaAleasa + 1 << " pentru intervalul " << ore[alegere - 1] << ".\n";
                std::cout << "Masa va fi pregatita pana la sosirea dumneavoastra.\n";
                std::cout << "Va asteptam cu drag!\n";
            }
        }
    } catch (const ExceptieFisier& e) {
        std::cout << "Eroare la rezervarea mesei: " << e.what() << std::endl;
    }
}

std::string ContPremium::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, (last - first + 1));
}

int ContPremium::getCaloriiById(int id) {
    std::ifstream fisier("Clienti.txt");
    if (!fisier.is_open()) {
        std::cout << "Eroare la deschiderea fisierului Clienti.txt!" << std::endl;
        return -1;
    }

    std::string linie;
    while (getline(fisier, linie)) {
        if (linie.starts_with("ID: ")) {
            int idFisier = std::stoi(linie.substr(4));
            if (idFisier == id) {
                while (getline(fisier, linie)) {
                    if (linie.starts_with("Calorii: ")) {
                        std::string caloriiStr = linie.substr(9);
                        caloriiStr = trim(caloriiStr);
                        try {
                            return std::stoi(caloriiStr);
                        } catch (const std::exception& e) {
                            std::cout << "Eroare la citirea caloriilor: " << e.what() << std::endl;
                            return -1;
                        }
                    }
                }
            }
        }
    }
    return -1;
}
