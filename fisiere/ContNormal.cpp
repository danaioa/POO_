#include "ContNormal.h"
#include<random>
ContNormal::ContNormal(int id_client, const std::string& nume, const std::string& telefon, const std::string& adresa)
    : Cont(id_client, nume, telefon, adresa) {}

double ContNormal::costlivrare() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 20);
    int costLivrare = dist(gen);
    return costLivrare;
}

std::unique_ptr<Cont> ContNormal::clone() const {
    return std::make_unique<ContNormal>(client->getId_Client(), client->getNume(),
                                         client->getTelefon(), client->getAdresa());
}
