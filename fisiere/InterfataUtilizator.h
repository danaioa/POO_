
#ifndef INTERFATA_UTILIZATOR_H
#define INTERFATA_UTILIZATOR_H

#include <memory>
#include <string>
#include "Client.h"
#include "MeniuPrincipal.h"


class InterfataUtilizator {
    std::unique_ptr<Client> client;
    bool trecePeste = false;
    int calorii{};
    double pret = 0;
    int id{};
    int ok=0;

public:
    InterfataUtilizator();

    void pornire();

    static bool verificaId(int id, std::unique_ptr<Client>& client);

    static void afiseazaOptiuneServire(const std::unique_ptr<Client>& client, InterfataUtilizator& interfata);

    static void afiseazaComanda(MeniuPrincipal& meniu, const std::unique_ptr<Client>& client);

    static void costuriInfunctieDeID(int id, double &pret);

    static std::string trim(const std::string& str);

    static int getCaloriiById(int id);

    static void afiseazaTipMeniu();

    static void afiseazaOptiuni(bool& trecePeste);

    static void creeazaContNou();
};

#endif // INTERFATA_UTILIZATOR_H
