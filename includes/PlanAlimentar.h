#ifndef PLANALIMENTAR_H
#define PLANALIMENTAR_H

#include <string>
#include <vector>
#include <random>
#include "MeniuItem.h"

class PlanAlimentar {
    int idClient;
    int calorii;

public:
    PlanAlimentar(int idClient, int caloriiDisponibile);

    static std::string trim(const std::string& str);
    static std::vector<MeniuItem> citesteProduseDinFisier(const std::string& fisier, const std::string& categorie);
    static void amestecaProduse(std::vector<MeniuItem>& produse);
    void construiesteMeniu(int nrZile, bool alegereManuala = false) const;
};

#endif // PLANALIMENTAR_H
