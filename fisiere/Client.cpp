#include "Client.h"
#include "Exceptii.h"

#include <algorithm>
#include <fstream>
#include <iostream>



Client::Client(int id, std::string nume, std::string telefon, std::string adresa, int nrComenzi, OptiuneServire optiune)
    : Nume(std::move(nume)), Telefon(std::move(telefon)), Adresa(std::move(adresa)), Optiune(optiune),
      Id_Client(id), varsta(0), gen(0), inaltime(0), greutate(0), NrComenzi(nrComenzi), pret(0) {}

Client& Client::operator=(Client other) {
    std::swap(Id_Client, other.Id_Client);
    std::swap(Nume, other.Nume);
    std::swap(Telefon, other.Telefon);
    std::swap(Adresa, other.Adresa);
    std::swap(pret, other.pret);
    std::swap(Optiune, other.Optiune);
    std::swap(varsta, other.varsta);
    std::swap(gen, other.gen);
    std::swap(inaltime, other.inaltime);
    std::swap(greutate, other.greutate);
    std::swap(NrComenzi, other.NrComenzi);
    return *this;
}


int Client::getPret() const {
    return pret;
}

void Client::setPret(double cost) {
    pret = static_cast<int>(cost);
}

int Client::getVarsta() const {
    return varsta;
}

const std::string& Client::getNume() const {
    return Nume;
}

const std::string& Client::getTelefon() const {
    return Telefon;
}

const std::string& Client::getAdresa() const {
    return Adresa;
}

int Client::getGen() const {
    return gen;
}

int Client::getInaltime() const {
    return inaltime;
}

int Client::getGreutate() const {
    return greutate;
}

int Client::getId_Client() const {
    return Id_Client;
}

int Client::getNrComenzi() const {
    return NrComenzi;
}

OptiuneServire Client::getOptiuneServire() const {
    return Optiune;
}



void Client::setOptiuneServire(OptiuneServire optiune) {
    Optiune = optiune;
}

void Client::actualizeazaNRComanda(int id) {
    std::ifstream fisier("Clienti.txt");
    if (!fisier.is_open()) {
        throw ExceptieFisier("Nu s-a putut deschide fișierul Clienti.txt.");
    }

    std::string linie;
    std::string continutFisier;

    while (std::getline(fisier, linie)) {
        if (linie.starts_with("ID: ")) {
            int idFisier = std::stoi(linie.substr(4));
            if (idFisier == id) {
                continutFisier += linie + "\n"; // ID

                while (std::getline(fisier, linie) && !linie.starts_with("NrComenzi: ")) {
                    continutFisier += linie + "\n";
                }

                int nrComenzi = std::stoi(linie.substr(11)) + 1;
                continutFisier += "NrComenzi: " + std::to_string(nrComenzi) + "\n";

                while (std::getline(fisier, linie)) {
                    continutFisier += linie + "\n";
                }
                break;
            }
        }

    }

    fisier.close();

    std::ofstream fisierOutput("Clienti.txt");
    if (!fisierOutput.is_open()) {
        throw ExceptieFisier("Nu s-a putut deschide fisierul pentru scriere.");
    }

    fisierOutput << continutFisier;
    fisierOutput.close();

    std::cout << "Numarul de comenzi a fost actualizat!" << std::endl;
}

int Client::citesteUltimulNumar(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "eroare la deschiderea fisierului!" << std::endl;
        return -1;
    }

    std::string linie;
    int ultimul_id = 0;

    while (std::getline(file, linie)) {
        size_t pos = linie.find("ID: ");
        if (pos == 0) {  // linia incepe cu "ID: "
            try {
                std::string id_str = linie.substr(4);
                int id = std::stoi(id_str);
                ultimul_id = id;
            }
            catch (const std::exception& e) {
                std::cout << "eroare la citirea ID-ului: " << e.what() << std::endl;
            }
        }
    }

    file.close();
    return ultimul_id;
}

int Client::generareCod() {
    int n = citesteUltimulNumar("Clienti.txt");
    n++;
    return n;
}
