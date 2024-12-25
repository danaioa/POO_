#include <random>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include "ContPremium.h"
#include "Exceptii.h"
#include "PlanAlimentar.h"

ContPremium::ContPremium(std::unique_ptr<Client> clientPtr)
    : Cont(clientPtr->getId_Client(), clientPtr->getNume(), clientPtr->getTelefon(), clientPtr->getAdresa()),
      obiectiv(nullptr), client(std::move(clientPtr)), greutate(0),  inaltime(0),  varsta(0), gen(0)  {}


ContPremium::ContPremium(int id, const std::string& nume, const std::string& telefon, const std::string& adresa)
    : Cont(id, nume, telefon, adresa), obiectiv(nullptr),  client(std::make_unique<Client>(id, nume, telefon, adresa)),
      greutate(0), inaltime(0), varsta(0), gen(0)  {}


ContPremium::~ContPremium() {
    delete obiectiv;
}

double ContPremium::getCostCont() {
    return costCont;
}

double ContPremium::costlivrare() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 20);
    double costLivrare = dist(gen);
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

[[maybe_unused]] void ContPremium::setDetaliiUtilizator(int greutate_, int inaltime_, int varsta_, int gen_) {
    greutate = greutate_;
    inaltime = inaltime_;
    varsta = varsta_;
    gen = gen_;
}

[[maybe_unused]]  void ContPremium::genereazaPlanAlimentar() const {
    int calorii = getCaloriiById(client->getId_Client());
    PlanAlimentar plan(client->getId_Client(), calorii);
    int nrZile = 7;
    plan.construiesteMeniu(nrZile, false);
    std::cout << "Comanda va ajunge in jurul orei 18:00 la adresa din cont.\n";
}

void ContPremium::rezervaMasa()
 {
        try {
             std::ifstream fisier("mese.txt");
            if (!fisier.is_open()) {
                throw ExceptieFisier ("Nu s-a putut deschide fișierul mese.txt.");
            }

             std::vector< std::pair<int, bool>> mese(5, { 0, false });
            string linie;


            int masaIndex = 0;
             std::vector<string> ore = {
                "18:00 - 20:00",
                "20:00 - 22:00",
                "22:00 - 00:00"
            };


            while (getline(fisier, linie)) {
                if (linie.find("rezervata") != string::npos) {
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

                std:: cin >> alegere;


                if (alegere < 1 || alegere > 3) {
                     std::cout << "Optiune invalida. Te rog alege un interval valid.\n";
                    continue;
                }


                size_t masaAleasa = -1;;
                for (size_t i = 0; i < mese.size(); ++i) {
                    if (!mese[i].second) {
                        masaAleasa = i;
                        break;
                    }
                }

                if (masaAleasa == -1) {
                     std::cout << "Nu mai sunt mese disponibile pentru acest interval.\n";
                     std::cout << "Te rugam sa alegi un alt interval.\n";
                }
                else {
                    intervalDisponibil = true;

                     std::cout << "Ai ales masa " << masaAleasa + 1 << " pentru intervalul " << ore[alegere - 1] << ".\n";
                    mese[masaAleasa].second = true;


                    std:: ofstream outFisier("mese.txt");
                    if (!outFisier.is_open()) {
                        throw ExceptieFisier ("Nu s-a putut deschide fișierul mese.txt pentru scriere.");
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
    }
    catch (const ExceptieFisier & e) {
         std::cout << "Eroare la rezervarea mesei: " << e.what() <<  std::endl;
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
         std::cout << "Eroare la deschiderea fisierului Clienti.txt!" <<  std::endl;
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
                        catch (const ExceptieOptiuneInvalida &e) {
                             std::cout << "Eroare la citirea caloriilor pentru clientul cu ID-ul " <<e.what()<< id <<  std::endl;
                            return -1;
                        }
                    }
                }
            }
        }
    }

    return -1;
}
