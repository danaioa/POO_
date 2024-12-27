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

    MeniuItem(MeniuItem&& other) noexcept;

    MeniuItem& operator=(MeniuItem&& other) noexcept;


    MeniuItem(const MeniuItem& other)=default;
    MeniuItem& operator=(const MeniuItem& other)=default;

    friend void swap(MeniuItem& lhs, MeniuItem& rhs) noexcept;
};

#endif // MENIUITEM_H
