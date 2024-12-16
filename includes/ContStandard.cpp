#include "ContStandard.h"
#include <random>

ContStandard::ContStandard(int id_client, const std::string& nume, const std::string& telefon, const std::string& adresa)
    : Cont(id_client, nume, telefon, adresa) {}

double ContStandard::getCostCont() {
    return costCont;
}

double ContStandard::costlivrare() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 20);
    double cost = dist(gen);
    cost *= 0.9;
    return cost;
}

std::unique_ptr<Cont> ContStandard::clone() const {
    return std::make_unique<ContStandard>(client->getId_Client(), client->getNume(),
                                         client->getTelefon(), client->getAdresa());
}
