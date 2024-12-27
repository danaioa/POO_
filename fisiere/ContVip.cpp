#include "ContVip.h"
#include "Obiectiv.h"
#include "PlanAlimentar.h"
#include "Sport.h"
#include "Exceptii.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <random>

ContVip::ContVip(int id_client, const std::string& nume, const std::string& telefon, const std::string& adresa,
                 int nrComenzi, OptiuneServire optiune, int pret)
    : Cont(id_client, nume, telefon, adresa, nrComenzi, optiune, pret), sportAles(Sport::Sala),
      antrenorAles("Default Nume", "Default Specializare", 0.0) {}

double ContVip::getCostCont() {
    return costCont;
}

/*void ContVip::setDetaliiUtilizator(int greutate_, int inaltime_, int varsta_, int gen_) {
    greutate = greutate_;
    inaltime = inaltime_;
    varsta = varsta_;
    gen = gen_;
}*/

double ContVip::costlivrare() {
    std::random_device rd;
    std::mt19937 randomGen(rd());
    std::uniform_int_distribution<> dist(1, 20);
    double costLivrare = dist(randomGen);
    costLivrare *= 0.75;
    return costLivrare;
}

void ContVip::setObiectiv(Obiectiv* obj) {
    delete obiectiv;
    obiectiv = obj;
}

Obiectiv* ContVip::alegeObiectiv() {
    int optiune;
    std::cout << "Alege obiectivul:\n";
    std::cout << "1. Slabire\n";
    std::cout << "2. Crestere masa musculara\n";
    std::cout << "3. Mentinere\n";
    std::cout << "Alegere: ";
    std::cin >> optiune;

    switch (optiune) {
        case 1: return new Slabire();
        case 2: return new MasaMusculara();
        case 3: return new Mentinere();
        default:
            throw ExceptieOptiuneInvalida();
    }
}

/*
int ContVip::calculeazaNecesarCaloric() const {
    if (obiectiv) {
        return obiectiv->calculeazaCalorii(greutate, inaltime, varsta, gen);
    }
    throw std::runtime_error("Obiectivul nu este setat.");
}
*/

/*void ContVip::genereazaPlanAlimentar() const {
    int calorii = getCaloriiById(client->getId_Client());
    PlanAlimentar plan(client->getId_Client(), calorii);

    int nrZile = 7;
    plan.construiesteMeniu(nrZile, false);
    std::cout << "Comanda va ajunge in jurul orei 18:00 la adresa din cont.\n";
}*/

void ContVip::rezervaMasa() {
    try {
        std::ifstream fisier("mese.txt");
        if (!fisier.is_open()) {
            throw ExceptieFisier("Nu s-a putut deschide fișierul mese.txt.");
        }

        std::vector<std::pair<int, bool>> mese(5, { 0, false });
        std::string linie;

        size_t masaIndex = 0;
        std::vector<std::string> ore = {"18:00 - 20:00", "20:00 - 22:00", "22:00 - 00:00"};

        while (std::getline(fisier, linie)) {
            if (linie.find("rezervata") != std::string::npos) {
                mese[masaIndex].second = true;
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

            auto masaAleasa = static_cast<size_t>(-1);
            for ( int  i = 0; i < mese.size(); ++i) {
                if (!mese[i].second) {
                    masaAleasa = i;
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
    }
    catch (const ExceptieFisier& e) {
        std::cout << "Eroare la rezervarea mesei: " << e.what() << std::endl;
    }
}

void ContVip::alegeSport() {
    std::cout << "Alege tipul de sport:\n";
    std::cout << "1. Sala\n";
    std::cout << "2. Inot\n";
    std::cout << "3. Yoga\n";
    std::cout << "4. Box\n";

    int alegere;
    std::cin >> alegere;

    if (alegere < 1 || alegere > 4) {
        std::cout << "Optiune invalida.\n";
        return;
    }

    sportAles = static_cast<Sport>(alegere - 1);
    std::cout << "Ai ales sportul: " << getSportString() << std::endl;

    alegeZiSiOra();
    verificaLocuriDisponibile();
}

std::string ContVip::getSportString() const {
    switch (sportAles) {
        case Sport::Sala: return "Sala";
        case Sport::Inot: return "Inot";
        case Sport::Yoga: return "Yoga";
        case Sport::Box: return "Box";
        default: return "Sport necunoscut";
    }
}

void ContVip::alegeAntrenor() {
    std::vector<Antrenor> antrenoriDisponibili;

    if (sportAles == Sport::Sala) {
        antrenoriDisponibili = {
            Antrenor("Ion Popescu", "Fitness", 50.0),
            Antrenor("Maria Ionescu", "Cardio", 60.0)
        };
    } else if (sportAles == Sport::Inot) {
        antrenoriDisponibili = {
            Antrenor("Vasile Georgescu", "Inot liber", 40.0),
            Antrenor("Ana Mihail", "Inot competitional", 55.0)
        };
    } else if (sportAles == Sport::Yoga) {
        antrenoriDisponibili = {
            Antrenor("Elena Popa", "Yoga", 70.0),
            Antrenor("Ioana Radu", "Yoga relaxare", 65.0)
        };
    } else if (sportAles == Sport::Box) {
        antrenoriDisponibili = {
            Antrenor("Florin Iulian", "Box", 75.0),
            Antrenor("Mihail Tudor", "Box profesionist", 85.0)
        };
    }

    std::cout << "Alege un antrenor:\n";
    for (size_t i = 0; i < antrenoriDisponibili.size(); ++i) {
        std::cout << i + 1 << ". " << antrenoriDisponibili[i].nume << " - " << antrenoriDisponibili[i].specializare
                 << " - " << antrenoriDisponibili[i].tarif << " lei/sesiune\n";
    }

    int alegereAntrenor;
    std::cin >> alegereAntrenor;

    if (alegereAntrenor < 1 || alegereAntrenor > static_cast<int>(antrenoriDisponibili.size())) {
        std::cout << "Optiune invalida.\n";
        return;
    }

    antrenorAles = antrenoriDisponibili[alegereAntrenor - 1];
    std::cout << "Ai ales antrenorul: " << antrenorAles.nume << ", specializare: " << antrenorAles.specializare << ".\n";
}

void ContVip::alegeZiSiOra() {
    std::vector<std::string> zileDisponibile = {"Luni", "Marti", "Miercuri", "Joi", "Vineri"};
    std::vector<std::string> oreDisponibile;

    if (sportAles == Sport::Sala) {
        oreDisponibile = {"08:00", "10:00", "12:00", "14:00", "16:00", "18:00"};
    } else if (sportAles == Sport::Inot) {
        oreDisponibile = {"09:00", "11:00", "13:00", "15:00", "17:00"};
    } else if (sportAles == Sport::Yoga) {
        oreDisponibile = {"07:00", "09:00", "11:00", "13:00", "15:00"};
    } else if (sportAles == Sport::Box) {
        oreDisponibile = {"08:00", "10:00", "12:00", "14:00", "16:00"};
    }

    std::cout << "Alege ziua pentru antrenament:\n";
    for (size_t i = 0; i < zileDisponibile.size(); ++i) {
        std::cout << i + 1 << ". " << zileDisponibile[i] << std::endl;
    }

    size_t ziAlesa;
    std::cin >> ziAlesa;

    if (ziAlesa < 1 || ziAlesa >= zileDisponibile.size()) {
        std::cout << "Ziua aleasa este invalida.\n";
        return;
    }

    std::cout << "Ai ales ziua: " << zileDisponibile[ziAlesa - 1] << std::endl;

    std::cout << "Alege ora pentru antrenament:\n";
    for (size_t i = 0; i < oreDisponibile.size(); ++i) {
        std::cout << i + 1 << ". " << oreDisponibile[i] << std::endl;
    }


    size_t oraAleasa;
    std::cin >> oraAleasa;

    if (oraAleasa < 1 || oraAleasa >= oreDisponibile.size()) {
        std::cout << "Ora aleasă este invalidă.\n";
        return;
    }

    std::cout << "Ai ales ora: " << oreDisponibile[oraAleasa - 1] << " pentru antrenament.\n";

    oraAleasaFinala = oreDisponibile[oraAleasa - 1];
    ziAleasaFinala = zileDisponibile[ziAlesa - 1];
}


void ContVip::verificaLocuriDisponibile() const {
    std::vector<int> locuriDisponibile = {5, 1, 3, 2, 1, 2};

    auto indexOra = static_cast<size_t>(-1);
    std::vector<std::string> oreDisponibile = {"08:00", "10:00", "12:00", "14:00", "16:00", "18:00"};

   for (size_t i = 0; i < oreDisponibile.size(); ++i) {
        if (oraAleasaFinala == oreDisponibile[i]) {
            indexOra = i;
            break;
        }
    }

    if (indexOra != -1 && locuriDisponibile[indexOra] > 0) {
        std::cout << "Locuri disponibile pentru ora aleasa.\n";
    } else {
        std::cout << "Nu mai sunt locuri disponibile pentru ora aleasa.\n";
    }
}


std::unique_ptr<Cont> ContVip::clone() const {
    return std::make_unique<ContVip>(client->getId_Client(), client->getNume(),
                                     client->getTelefon(), client->getAdresa(),
                                     client->getNrComenzi(), client->getOptiuneServire(), client->getPret());
}


std::string ContVip::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, (last - first + 1));
}


int ContVip::getCaloriiById(int id) {
    std::ifstream fisier("Clienti.txt");
    if (!fisier.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului Clienti.txt!" << std::endl;
        return -1;
    }

    std::string linie;
    while (std::getline(fisier, linie)) {
        if (linie.starts_with("ID: ")) {
            int idFisier = std::stoi(linie.substr(4));
            if (idFisier == id) {
                while (std::getline(fisier, linie)) {
                    if (linie.starts_with("Calorii: ")) {
                        std::string caloriiStr = linie.substr(9);
                        caloriiStr = trim(caloriiStr);

                        try {
                            return std::stoi(caloriiStr);
                        } catch (const std::invalid_argument&) {
                            std::cout << "Eroare la citirea caloriilor pentru clientul cu ID-ul " << id << std::endl;
                            return -1;
                        }
                    }
                }
            }
        }
    }

    return -1;
}
