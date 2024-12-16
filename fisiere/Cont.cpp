#include "Cont.h"
#include <fstream>
#include <algorithm>
#include <iostream>


Cont::Cont(int id_client, const std::string& nume, const std::string& telefon, const std::string& adresa,
           int nrComenzi, OptiuneServire optiune, int pret)
    : client(std::make_unique<Client>(id_client, nume, telefon, adresa, nrComenzi, optiune)), PretCont(pret) {}


Cont::Cont(Cont&& other) noexcept
    : client(std::move(other.client)), PretCont(other.PretCont) {}

void Cont::salveazaInFisier() const {
    std::ofstream outFile("clienti.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << "ID Client: " << client->getId_Client() << "\n";
        outFile << "Nume: " << client->getNume() << "\n";
        outFile << "Telefon: " << client->getTelefon() << "\n";
        outFile << "Adresa: " << client->getAdresa() << "\n";
        outFile << "Optiune Servire: "
                << (client->getOptiuneServire() == OptiuneServire::LaPachet ? "La Pachet" : "Restaurant") << "\n";
        outFile << "Numar Comenzi: " << client->getNrComenzi() << "\n";
        outFile << "Pret: " << client->getPret() << "\n";
        outFile << "-----------------------\n";
    } else {
        std::cout << "Eroare la deschiderea fișierului pentru salvare!" << std::endl;
    }
}

int Cont::citesteUltimulNumar(const std::string& filename, int prefix) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Eroare la deschiderea fișierului!" << std::endl;
        return -1;
    }

    std::string linie;
    int ultimul_id = -1;

    while (std::getline(file, linie)) {
        if (linie.find("ID:") == 0) {
            try {
                int id = std::stoi(linie.substr(4));
                if (id / 100 == prefix) {
                    ultimul_id = std::max(ultimul_id, id);
                }
            } catch (const std::exception& e) {
                std::cout << "Eroare la citirea ID-ului: " << e.what() << std::endl;
            }
        }
    }
    file.close();
    return ultimul_id;
}

int Cont::generareCod(int prefix) {
    int n = citesteUltimulNumar("Clienti.txt", prefix);
    if (n == -1) {
        return prefix * 100 + 1;
    }
    return ++n;
}


