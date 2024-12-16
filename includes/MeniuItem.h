#ifndef MENIUITEM_H
#define MENIUITEM_H

#include <string>

class MeniuItem {
public:
    std::string nume;
    int calorii;
    float pret;
    std::string categorie;

    MeniuItem(std::string n, int c, float p, std::string cat);
    MeniuItem(const MeniuItem& other) = default;
};

#endif // MENIUITEM_H
