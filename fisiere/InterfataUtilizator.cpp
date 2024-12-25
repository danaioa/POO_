
#include "InterfataUtilizator.h"
#include "Client.h"
#include "ClientNou.h"
#include "ContVip.h"
#include "ContNormal.h"
#include "ContStandard.h"
#include "ContPremium.h"
#include "OptiuneServire.h"
#include "MeniuPrincipal.h"
#include "Produs.h"
#include "PlanAlimentar.h"
//#include "ProdusException.h"
#include "Exceptii.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>



InterfataUtilizator::InterfataUtilizator() : client(nullptr) {}

void InterfataUtilizator::pornire() {
    cout << "      Bine ati venit la HELLO FRESH!\n";
    cout << "     -------------------------------\n";

    while (true) {
        if (!trecePeste) {
            cout << "Introduceti ID-ul: ";
            std::cin >> id;

            try {
                if (verificaId(id, client)) {
                    cout << "ID valid! Puteti comanda mancare.\n";
                    if (id / 100 == 33 || id / 100 == 44) {
                        int optiuneBox, generare;
                        cout << "Doriti sa comandati un plan alimentar (la pachet)? (1 - Da, 0 - Nu): ";
                        std:: cin >> optiuneBox;
                        cout << "Doriti sa generam noi un meniu personalizat pentru dumneavoastra? (1-Da, 0-Nu): ";
                         std::cin >> generare;

                        if (optiuneBox == 1) {
                            int nrzile;
                            ok=1;
                            client->setOptiuneServire(LaPachet);
                            cout << "Pentru cate zile doriti planul alimentar: ";
                            std::cin >> nrzile;

                            if (generare == 1) {
                                calorii = getCaloriiById(client->getId_Client());
                                PlanAlimentar plan(client->getId_Client(), calorii);
                                plan.construiesteMeniu(nrzile, false);
                                cout << "Comanda va ajunge in jurul orei 18:00 la adresa din cont.\n";
                                Client::actualizeazaNRComanda(id);
                            } else {
                                calorii = getCaloriiById(client->getId_Client());
                                PlanAlimentar plan(client->getId_Client(), calorii);
                                plan.construiesteMeniu(nrzile, true);
                                cout << "---Comanda a fost plasata-----\n";
                                cout << "---Va ajunge in jurul orei 18:00 la adresa din cont";
                            }
                        }

                    }


                    if (ok==0 && (id / 100 == 33 || id / 100 == 44)) {
                        int optiuneServire;
                        cout << "Alege optiunea de servire:\n";
                        cout << "1. La restaurant (rezervare masa)\n";
                        cout << "2. La pachet\n";
                        cout << "Alegere: ";
                         std::cin >> optiuneServire;

                        try {
                            switch (optiuneServire) {
                            case 1: {
                                client->setOptiuneServire(InRestaurant);
                                if (id / 100 == 33) {
                                    ContVip::rezervaMasa();
                                }
                                break;
                            }
                            case 2:
                                client->setOptiuneServire(LaPachet);
                                break;
                            default:
                                throw ExceptieOptiuneInvalida("Optiune invalida.");
                            }
                        } catch (const ExceptieOptiuneInvalida& e) {
                            cout << e.what() << endl;
                            continue;
                        }
                    }

                    MeniuPrincipal meniu;
                    afiseazaComanda(meniu, client);
                    break;
                } else {
                    afiseazaOptiuni(trecePeste);
                }

            } catch (const ExceptieFisier& e) {
                cout << "Eroare la citirea fisierului: " << e.what() << endl;
            }
        } else {

            client = make_unique<Client>(-1, "Client fara cont", "Necunoscut", "Necunoscut");
            MeniuPrincipal meniu;
            afiseazaComanda(meniu, client);
            break;
        }
    }
}


void InterfataUtilizator::afiseazaComanda(MeniuPrincipal& meniu, const std::unique_ptr<Client>& client) {
    int optiune;
    bool continuare = true;
    std::vector<std::pair<std::unique_ptr<Produs>, int>> comanda;
    double total = 0;

    while (continuare) {
        afiseazaTipMeniu();
        std::cin >> optiune;

        switch (optiune) {
        case 1:
            meniu.citesteProduseDinFisier("meniu.txt");
            break;
        case 2:
            meniu.citesteProduseDinFisier("meniuBar.txt");
            break;
        case 3:
            meniu.citesteProduseDinFisier("meniuDesert.txt");
            break;
        default:
            std::cout << "Optiune invalida. Te rog alege din nou.\n";
            continue;
        }

        meniu.afiseazaMeniu();

        std::cout << "Alege un produs (indice): ";
        int produsSelectat;
        std::cin >> produsSelectat;

        if (produsSelectat > 0 && produsSelectat <= static_cast<int>(meniu.getNrProduse())) {
            const auto& produs = meniu.getProduse()[produsSelectat - 1];
            std::cout << "Ai ales: " << produs->getNume() << "\n";

            int cantitate;
            std::cout << "Cate portii doresti? ";
            std::cin >> cantitate;

            comanda.emplace_back(produs->clone(), cantitate);
            std::cout << "Ai adaugat " << cantitate << " portii de " << produs->getNume() << "\n";

            total += produs->getPret() * cantitate;
        } else {
            std::cout << "Index invalid!\n";
        }

        std::cout << "Vrei sa adaugi alt produs? (1 pentru da, 0 pentru nu): ";
        std::cin >> continuare;
    }

    std::cout << "\n--- Comanda Finala ---\n";
    if (client) {
        std::cout << "Client: " << client->getNume() << "\n";
        std::cout << "ID_CLIENT: " << client->getId_Client() << "\n";
        std::cout << "Telefon: " << client->getTelefon() << "\n";
        std::cout << "Adresa: " << client->getAdresa() << "\n";
    } else {
        std::cout << "Client:------\n";
    }

    for (const auto& [produs, cantitate] : comanda) {
        std::cout << "Produs: " << produs->getNume()
             << ", Cantitate: " << cantitate
             << ", Pret unitar: " << produs->getPret() << " lei\n";
    }

    if (client) {
        if (client->getNrComenzi() % 5 == 0) {
            std::cout << "Reducere de 20% aplicata!\n";
            total *= 0.8;  // Reducere de 20%
        }

        if (dynamic_cast<ClientNou*>(client.get())) {
            std::cout << "Reducere de 25% aplicata pentru clientul nou!\n";
            total *= 0.75;  // Reducere de 25%
        }

        costuriInfunctieDeID(client->getId_Client(), total);
        Client::actualizeazaNRComanda(client->getId_Client());
    }

    std::cout << "Total de plata cu tot cu livrare : " << total << " lei\n";
}


bool InterfataUtilizator::verificaId(int id, std::unique_ptr<Client>& client) {
    std::ifstream fisier("Clienti.txt");
    if (!fisier.is_open()) {
        throw ExceptieFisier("Nu s-a putut deschide fisierul Clienti.txt.");
    }

    std::string linie;
    while (std::getline(fisier, linie)) {
        if (linie.starts_with("ID: ")) {
            int idFisier = std::stoi(linie.substr(4));
            if (idFisier == id) {
                std::string nume, telefon, adresa;
                int nrComenzi = 0;
                std::getline(fisier, linie);
                if (linie.starts_with("Nume: ")) nume = linie.substr(6);
                std::getline(fisier, linie);
                if (linie.starts_with("Telefon: ")) telefon = linie.substr(9);
                std::getline(fisier, linie);
                if (linie.starts_with("Adresa: ")) adresa = linie.substr(8);
                std::getline(fisier, linie);
                if (linie.starts_with("NrComenzi: ")) nrComenzi = std::stoi(linie.substr(11));

                client = std::make_unique<Client>(idFisier, nume, telefon, adresa, nrComenzi);
                return true;
            }
        }
    }

    return false;
}


void InterfataUtilizator::costuriInfunctieDeID(int id, double& pret) {
    if(id / 100 == 11) {
        ContNormal contNormal(0, "Nume", "Telefon", "Adresa");
        pret += contNormal.costlivrare();
    }

    if(id / 100 == 22) {
        ContStandard contStandard(0, "Nume", "Telefon", "Adresa");
        pret += contStandard.costlivrare();
    }

    if(id / 100 == 33) {
        ContPremium contPremium(0, "Nume", "Telefon", "Adresa");
        pret += contPremium.costlivrare();
    }

    if(id / 100 == 44) {
        ContVip contVip(0, "Nume", "Telefon", "Adresa");
        pret += contVip.costlivrare();
    }
}

std::string InterfataUtilizator::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, (last - first + 1));
}

int InterfataUtilizator::getCaloriiById(int id) {
    std::ifstream fisier("Clienti.txt");
    if (!fisier.is_open()) {
        std::cout << "Eroare la deschiderea fisierului Clienti.txt!" << std::endl;
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
                        }
                        catch (const std::invalid_argument&) {
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

void InterfataUtilizator::afiseazaTipMeniu() {
    std::cout << "\nAlege tipul de produs:\n";
    std::cout << "1. Mancare\n";
    std::cout << "2. Bauturi\n";
    std::cout << "3. Deserturi\n";
}

void InterfataUtilizator::afiseazaOptiuni(bool& trecePeste) {
    std::cout << "ID invalid. Alegeti o optiune:\n";
    std::cout << "1. Creeaza un cont nou\n";
    std::cout << "2. Treci peste\n";
    std::cout << "3. Mai incearca\n";

    int optiune;
    std::cin >> optiune;

    switch (optiune) {
        case 1:
            creeazaContNou();
        break;

        case 2: {
            std::cout << "Comanda fara cont.\n";
            trecePeste = true;
            break;
        }
        case 3:
            std::cout << "Reincercati sa introduceti ID-ul.\n";
        break;
        default:
            std::cout << "Optiune invalida. Reincercati.\n";
    }
}


void InterfataUtilizator::creeazaContNou() {
    ClientNou clientNou;
    clientNou.citesteDate();
    clientNou.salveazaInFisier("Clienti.txt");
    std::cout << "Client salvat cu succes!\n";

    std::cout << "ID-ul clientului: " << clientNou.getId_Client() << "\n";

    if (const auto& obiectiv = clientNou.getObiectiv()) {
        std::cout << "Obiectivul ales: " << obiectiv->getObiectivString() << "\n";

        int calorii = obiectiv->calculeazaCalorii(clientNou.getGreutate(), clientNou.getInaltime(), clientNou.getVarsta(), clientNou.getGen());
        std::cout << "Caloriile necesare: " << calorii << "\n";
    }
}