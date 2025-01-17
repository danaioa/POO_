#ifndef PLAN_ALIMENTAR_H
#define PLAN_ALIMENTAR_H
#include <vector>
#include <string>
#include <iomanip>
#include "MeniuItem.h"

using namespace std;

class PlanAlimentar {
private:
    int idClient;
    int calorii;

public:
    PlanAlimentar(int idClient, int caloriiDisponibile);

    static string trim(const string& str);

    static vector<MeniuItem> citesteProduseDinFisier(const string& fisier, const string& categorie);

    static void amestecaProduse(vector<MeniuItem>& produse);

    void construiesteMeniu(int nrZile) const;


};

string trim(const string& str);
int getCaloriiById(int id);

#endif // PLAN_ALIMENTAR_H
